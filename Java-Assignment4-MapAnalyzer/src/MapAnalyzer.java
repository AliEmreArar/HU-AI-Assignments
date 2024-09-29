import java.io.*;
import java.util.*;

/**
 * Represents the result of a route finding operation.
 */
class Result {
    List<Integer> path;
    Integer distance;

    /**
     * Constructs a Result object.
     *
     * @param path     The list of road IDs representing the path.
     * @param distance The total distance of the path.
     */
    Result(List<Integer> path, Integer distance) {
        this.path = path;
        this.distance = distance;
    }
}

/**
 * Represents a road between two points.
 */
class Road implements Comparable<Road> {
    int roadId;
    String point1;
    String point2;
    int distance;

    /**
     * Constructs a Road object.
     *
     * @param roadId  The unique identifier of the road.
     * @param point1  The starting point of the road.
     * @param point2  The ending point of the road.
     * @param distance The distance of the road.
     */
    Road(int roadId, String point1, String point2, int distance) {
        this.roadId = roadId;
        this.point1 = point1;
        this.point2 = point2;
        this.distance = distance;
    }

    @Override
    public int compareTo(Road other) {
        if (this.distance == other.distance) {
            return Integer.compare(this.roadId, other.roadId);
        }
        return Integer.compare(this.distance, other.distance);
    }
}

/**
 * Represents a road between two points in a simplified form.
 */
class RoadObject {
    int distance;
    int roadId;
    String point1;
    String point2;

    /**
     * Constructs a RoadObject.
     *
     * @param distance The distance of the road.
     * @param roadId   The unique identifier of the road.
     * @param point1   The starting point of the road.
     * @param point2   The ending point of the road.
     */
    RoadObject(int distance, int roadId, String point1, String point2) {
        this.distance = distance;
        this.roadId = roadId;
        this.point1 = point1;
        this.point2 = point2;
    }
}

/**
 * This class analyzes maps and finds routes between specified points.
 */
public class MapAnalyzer {
    /**
     * Main method to analyze maps and find routes.
     *
     * @param args Command-line arguments. The first argument should be the input
     *             file path, and the second argument should be the output file
     *             path.
     */
    public static void main(String[] args) {
        String inputFile = args[0];
        String outputFile = args[1];
        try {
            BufferedReader reader = new BufferedReader(new FileReader(inputFile));
            BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));

            String[] firstLine = reader.readLine().split("\t");
            String start = firstLine[0];
            String destination = firstLine[1];

            //Keeps all paths by id value
            HashMap<Integer, Road> values = new HashMap<>();

            List<Road> roads = new ArrayList<>();
            String line;
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\t");
                int roadId = Integer.parseInt(parts[3]);
                roads.add(new Road(roadId, parts[0], parts[1], Integer.parseInt(parts[2])));
                values.put(roadId, new Road(roadId, parts[0], parts[1], Integer.parseInt(parts[2])));
            }
            reader.close();

            // Calculate the shortest path on normal map
            Map<String, List<RoadObject>> roadMap = convertToMap(convertRoadsToRoadObjects(roads));
            Result normalRoute = findFastestRoute(start, destination, roadMap);
            writer.write("Fastest Route from " + start + " to " + destination + " (" + normalRoute.distance + " KM):\n");
            for (int roadId : normalRoute.path) {
                writer.write(values.get(roadId).point1 + "\t" + values.get(roadId).point2 + "\t" + values.get(roadId).distance + "\t" + roadId + "\n");
            }

            // Creating a barely connected map
            List<RoadObject> barelyConnectedMap = buildBarelyConnectedMap(roads);
            writer.write("Roads of Barely Connected Map is:\n");
            int totalBarelyDistance = 0;
            for (RoadObject road : barelyConnectedMap) {
                writer.write(road.point1 + "\t" + road.point2 + "\t" + road.distance + "\t" + road.roadId + "\n");
                totalBarelyDistance += road.distance;
            }

            // Calculate the shortest path in Barely connected map
            Map<String, List<RoadObject>> barelyConnectedRoadMap = convertToMap(barelyConnectedMap);
            Result barelyConnectedRoute = findFastestRoute(start, destination, barelyConnectedRoadMap);
            writer.write("Fastest Route from " + start + " to " + destination + " on Barely Connected Map (" + barelyConnectedRoute.distance + " KM):\n");
            for (int roadId : barelyConnectedRoute.path) {
                writer.write(values.get(roadId).point1 + "\t" + values.get(roadId).point2 + "\t" + values.get(roadId).distance + "\t" + roadId + "\n");
            }

            int totalDistance = 0;
            for (Road i : values.values()) {
                totalDistance += i.distance;
            }

            double ratio = (double) totalBarelyDistance / totalDistance;
            String formattedRatio = String.format("%.2f", ratio);

            double ratio2 = (double) barelyConnectedRoute.distance / normalRoute.distance;
            String formattedRatio2 = String.format("%.2f", ratio2);

            writer.write("Analysis:\n");
            writer.write("Ratio of Construction Material Usage Between Barely Connected and Original Map: " + formattedRatio + "\n");
            writer.write("Ratio of Fastest Route Between Barely Connected and Original Map: " + formattedRatio2);
            writer.flush();
            writer.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Builds a barely connected map from a list of roads.
     *
     * @param roads The list of roads.
     * @return A list of road objects representing the barely connected map.
     */
    public static List<RoadObject> buildBarelyConnectedMap(List<Road> roads) {
        List<RoadObject> barelyConnectedMap = new ArrayList<>();
        Set<String> allPoints = new TreeSet<>();

        // Collect all dots
        for (Road road : roads) {
            allPoints.add(road.point1);
            allPoints.add(road.point2);
        }

        // Sort roads by distance and road ID
        Collections.sort(roads);

        // Create Union-Find structure
        Map<String, String> parent = new HashMap<>();
        for (String point : allPoints) {
            parent.put(point, point);
        }

        class UnionFind {
            Map<String, String> parent;

            UnionFind(Map<String, String> parent) {
                this.parent = parent;
            }

            String find(String point) {
                if (parent.get(point).equals(point)) {
                    return point;
                }
                String root = find(parent.get(point));
                parent.put(point, root);
                return root;
            }

            void union(String point1, String point2) {
                String root1 = find(point1);
                String root2 = find(point2);
                parent.put(root1, root2);
            }
        }

        UnionFind uf = new UnionFind(parent);

        // Creating minimum spanning tree with Kruskal algorithm
        for (Road road : roads) {
            String point1 = road.point1;
            String point2 = road.point2;
            if (!uf.find(point1).equals(uf.find(point2))) {
                barelyConnectedMap.add(new RoadObject(road.distance, road.roadId, point1, point2));
                uf.union(point1, point2);
            }
            // Stop if we connected all the dots
            if (barelyConnectedMap.size() == allPoints.size() - 1) {
                break;
            }
        }

        return barelyConnectedMap;
    }

    /**
     * Converts a list of roads to a list of road objects.
     *
     * @param roads The list of roads.
     * @return A list of road objects.
     */
    public static List<RoadObject> convertRoadsToRoadObjects(List<Road> roads) {
        List<RoadObject> roadObjects = new ArrayList<>();
        for (Road road : roads) {
            roadObjects.add(new RoadObject(road.distance, road.roadId, road.point1, road.point2));
        }
        return roadObjects;
    }

    /**
     * Converts a list of road objects to a map.
     *
     * @param roadObjects The list of road objects.
     * @return A map representation of the road objects.
     */
    public static Map<String, List<RoadObject>> convertToMap(List<RoadObject> roadObjects) {
        Map<String, List<RoadObject>> roadMap = new HashMap<>();
        for (RoadObject road : roadObjects) {
            roadMap.putIfAbsent(road.point1, new ArrayList<>());
            roadMap.putIfAbsent(road.point2, new ArrayList<>());
            roadMap.get(road.point1).add(road);
            roadMap.get(road.point2).add(road);
        }
        return roadMap;
    }

    /**
     * Finds the fastest route between two points using Dijkstra's algorithm.
     *
     * @param start       The starting point.
     * @param destination The destination point.
     * @param roads       The map representation of the roads.
     * @return The result containing the path and distance of the fastest route.
     */
    public static Result findFastestRoute(String start, String destination, Map<String, List<RoadObject>> roads) {
        // Priority queue to prioritize roads first by distance, then by roadId
        PriorityQueue<RoadObject> priorityQueue = new PriorityQueue<>(Comparator.comparingInt((RoadObject ro) -> ro.distance).thenComparingInt(ro -> ro.roadId));
        Map<String, Integer> distances = new HashMap<>();
        Map<String, Integer> previous = new HashMap<>();
        Map<String, Integer> initialSegmentDistance = new HashMap<>();
        Set<String> visited = new HashSet<>();

        for (String point : roads.keySet()) {
            distances.put(point, Integer.MAX_VALUE);
            initialSegmentDistance.put(point, Integer.MAX_VALUE);
        }
        distances.put(start, 0);
        initialSegmentDistance.put(start, 0);
        priorityQueue.add(new RoadObject(0, -1, start, start));

        while (!priorityQueue.isEmpty()) {
            RoadObject closestRoadObject = priorityQueue.poll();
            String currentPoint = closestRoadObject.point2;

            if (visited.contains(currentPoint)) {
                continue;
            }

            visited.add(currentPoint);

            if (currentPoint.equals(destination)) {
                break;
            }

            for (RoadObject road : roads.get(currentPoint)) {
                String nextPoint = road.point1.equals(currentPoint) ? road.point2 : road.point1;
                int newDist = distances.get(currentPoint) + road.distance;
                int newInitialSegmentDist = closestRoadObject.distance == 0 ? road.distance : initialSegmentDistance.get(currentPoint);

                if (newDist < distances.get(nextPoint) ||
                        (newDist == distances.get(nextPoint) && newInitialSegmentDist < initialSegmentDistance.get(nextPoint)) ||
                        (newDist == distances.get(nextPoint) && newInitialSegmentDist == initialSegmentDistance.get(nextPoint) && road.roadId < previous.getOrDefault(nextPoint, Integer.MAX_VALUE))) {
                    distances.put(nextPoint, newDist);
                    previous.put(nextPoint, road.roadId);
                    initialSegmentDistance.put(nextPoint, newInitialSegmentDist);
                    priorityQueue.add(new RoadObject(newDist, road.roadId, currentPoint, nextPoint));
                }
            }
        }

        // Create final route
        List<Integer> path = new ArrayList<>();
        Integer distance = distances.get(destination);

        if (distance != Integer.MAX_VALUE) {
            String currentPoint = destination;

            while (!currentPoint.equals(start)) {
                Integer roadId = previous.get(currentPoint);
                path.add(roadId);
                for (RoadObject road : roads.get(currentPoint)) {
                    if (road.roadId == roadId) {
                        currentPoint = road.point1.equals(currentPoint) ? road.point2 : road.point1;
                        break;
                    }
                }
            }
            // Sort road by route order
            Collections.reverse(path);
        }

        return new Result(path, distance);
    }
}
