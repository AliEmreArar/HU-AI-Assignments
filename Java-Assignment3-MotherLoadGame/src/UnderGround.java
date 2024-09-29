/**
 * Represents an underground resource.
 */
public class UnderGround {

    private boolean isDigging;
    private boolean isDangerous;
    private boolean hasValue;
    private int xAxis;
    private int yAxis;
    private int mass;
    private int worth;

    /**
     * Constructs an UnderGround object with specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public UnderGround(int xAxis, int yAxis) {
        this.xAxis = xAxis;
        this.yAxis = yAxis;
    }

    /**
     * Checks if digging is allowed.
     *
     * @return True if digging is allowed, false otherwise.
     */
    public boolean isDigging() {
        return isDigging;
    }

    /**
     * Checks if the resource is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    public boolean isDangerous() {
        return isDangerous;
    }

    /**
     * Checks if the resource has value.
     *
     * @return True if valuable, false otherwise.
     */
    public boolean isHasValue() {
        return hasValue;
    }

    /**
     * Gets the mass of the resource.
     *
     * @return The mass value.
     */
    public int getMass() {
        return mass;
    }

    /**
     * Gets the worth of the resource.
     *
     * @return The worth value.
     */
    public int getWorth() {
        return worth;
    }
}

/**
 * Represents soil as an underground resource.
 */
class Soil extends UnderGround {

    /**
     * Constructs a Soil object with specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Soil(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    @Override
    public boolean isDangerous() {
        return false;
    }

    @Override
    public boolean isHasValue() {
        return false;
    }

    @Override
    public boolean isDigging() {
        return true;
    }
}

/**
 * Represents a ruby as an underground resource.
 */
class Ruby extends UnderGround {

    /**
     * Constructs a Ruby object with specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Ruby(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    @Override
    public int getMass() {
        return 80;
    }

    @Override
    public int getWorth() {
        return 20000;
    }

    @Override
    public boolean isDangerous() {
        return false;
    }

    @Override
    public boolean isHasValue() {
        return true;
    }

    @Override
    public boolean isDigging() {
        return true;
    }
}

/**
 * Represents an obstacle in the underground world.
 */
class Obstacle extends UnderGround {

    public Obstacle(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Determines if this obstacle can be dug through.
     *
     * @return true if it can be dug through, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return false;
    }

    /**
     * Determines if this obstacle is dangerous.
     *
     * @return true if it is dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Determines if this obstacle has any value.
     *
     * @return true if it has value, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return false;
    }
}

/**
 * Represents lava in the underground world.
 */
class Lava extends UnderGround {

    public Lava(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Determines if lava can be dug through.
     *
     * @return true if it can be dug through, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return false;
    }

    /**
     * Determines if lava is dangerous.
     *
     * @return true if it is dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return true;
    }

    /**
     * Determines if lava has any value.
     *
     * @return true if it has value, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return false;
    }
}
/**
 * Represents a type of material found underground called Goldium.
 */
class Goldium extends UnderGround {

    /**
     * Constructs a new Goldium instance with the specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Goldium(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Gets the mass of Goldium.
     *
     * @return The mass in grams.
     */
    @Override
    public int getMass() {
        return 20;
    }

    /**
     * Gets the monetary worth of Goldium.
     *
     * @return The value in currency (e.g., dollars).
     */
    @Override
    public int getWorth() {
        return 250;
    }

    /**
     * Determines if Goldium is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Indicates whether Goldium has any value.
     *
     * @return True if valuable, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return true;
    }

    /**
     * Checks if Goldium can be dug.
     *
     * @return True if it can be dug, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return true;
    }
}
/**
 * Represents a type of material found underground called Emerald.
 */
class Emerald extends UnderGround {

    /**
     * Constructs a new Emerald instance with the specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Emerald(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Gets the mass of Emerald.
     *
     * @return The mass in grams.
     */
    @Override
    public int getMass() {
        return 60;
    }

    /**
     * Gets the monetary worth of Emerald.
     *
     * @return The value in currency (e.g., dollars).
     */
    @Override
    public int getWorth() {
        return 5000;
    }

    /**
     * Determines if Emerald is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Indicates whether Emerald has any value.
     *
     * @return True if valuable, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return true;
    }

    /**
     * Checks if Emerald can be dug.
     *
     * @return True if it can be dug, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return true;
    }
}
/**
 * Represents a type of material found underground called Einsteinium.
 */
class Einsteinium extends UnderGround {

    /**
     * Constructs a new Einsteinium instance with the specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Einsteinium(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Gets the mass of Einsteinium.
     *
     * @return The mass in grams.
     */
    @Override
    public int getMass() {
        return 40;
    }

    /**
     * Gets the monetary worth of Einsteinium.
     *
     * @return The value in currency (e.g., dollars).
     */
    @Override
    public int getWorth() {
        return 2000;
    }

    /**
     * Determines if Einsteinium is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Indicates whether Einsteinium has any value.
     *
     * @return True if valuable, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return true;
    }

    /**
     * Checks if Einsteinium can be dug.
     *
     * @return True if it can be dug, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return true;
    }
}
/**
 * Represents a type of material found underground called Diamond.
 */
class Diamond extends UnderGround {

    /**
     * Constructs a new Diamond instance with the specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Diamond(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Gets the mass of Diamond.
     *
     * @return The mass in grams.
     */
    @Override
    public int getMass() {
        return 100;
    }

    /**
     * Gets the monetary worth of Diamond.
     *
     * @return The value in currency (e.g., dollars).
     */
    @Override
    public int getWorth() {
        return 100000;
    }

    /**
     * Determines if Diamond is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Indicates whether Diamond has any value.
     *
     * @return True if valuable, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return true;
    }

    /**
     * Checks if Diamond can be dug.
     *
     * @return True if it can be dug, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return true;
    }
}

/**
 * Represents a type of material found underground called Amazonite.
 */
class Amazonite extends UnderGround {

    /**
     * Constructs a new Amazonite instance with the specified coordinates.
     *
     * @param xAxis The x-coordinate.
     * @param yAxis The y-coordinate.
     */
    public Amazonite(int xAxis, int yAxis) {
        super(xAxis, yAxis);
    }

    /**
     * Gets the mass of Amazonite.
     *
     * @return The mass in grams.
     */
    @Override
    public int getMass() {
        return 120;
    }

    /**
     * Gets the monetary worth of Amazonite.
     *
     * @return The value in currency (e.g., dollars).
     */
    @Override
    public int getWorth() {
        return 500000;
    }

    /**
     * Determines if Amazonite is dangerous.
     *
     * @return True if dangerous, false otherwise.
     */
    @Override
    public boolean isDangerous() {
        return false;
    }

    /**
     * Indicates whether Amazonite has any value.
     *
     * @return True if valuable, false otherwise.
     */
    @Override
    public boolean isHasValue() {
        return true;
    }

    /**
     * Checks if Amazonite can be dug.
     *
     * @return True if it can be dug, false otherwise.
     */
    @Override
    public boolean isDigging() {
        return true;
    }
}

