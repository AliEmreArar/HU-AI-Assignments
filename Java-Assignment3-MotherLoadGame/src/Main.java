import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
import javafx.scene.input.KeyEvent;
import javafx.util.Duration;
import java.util.*;

public class Main extends Application {
    Map<String , UnderGround> blocks = new HashMap<>();
    int DrillMass =0;
    int DrillValue = 0;
    int fuelValue = 10000;

    public static void main(String[] args) {
        launch(args);
    }
    /**
     * The entry point for the JavaFX application. Initializes the game interface and sets up the scene.
     *
     * @param stage The primary stage for the application.
     */
    @Override
    public void start(Stage stage){

        Image obstacle = new Image("assets/underground/obstacle_01.png");
        Image soil = new Image("assets/underground/soil_01.png");
        Image top = new Image("assets/underground/top_01.png");
        Image lava = new Image("assets/underground/lava_01.png");
        Image amazonite = new Image("assets/underground/valuable_amazonite.png");
        Image emerald = new Image("assets/underground/valuable_emerald.png");
        Image goldium = new Image("assets/underground/valuable_goldium.png");
        Image rightDrill = new Image("assets/drill/drill_60.png");
        Image einsteinium = new Image("assets/underground/valuable_einsteinium.png");
        Image ruby = new Image("assets/underground/valuable_ruby.png");
        Image diamond = new Image("assets/underground/valuable_diamond.png");

        ImageView imageViewRight = new ImageView(rightDrill);
        imageViewRight.setPreserveRatio(true);
        imageViewRight.setFitWidth(50);
        imageViewRight.setFitHeight(50);

        List<Image> randomImages = new ArrayList<>();

        Collections.addAll(randomImages, lava, soil, obstacle, soil, amazonite, soil, emerald, soil, goldium, soil,einsteinium,soil,ruby,soil,diamond,soil,soil,soil,soil);

        GridPane gridPane = new GridPane();
        gridPane.setStyle("-fx-background-color: brown;");

        StackPane redScreen = new StackPane();
        redScreen.setStyle("-fx-background-color: red");
        redScreen.setVisible(false);

        StackPane greenScreen = new StackPane();
        greenScreen.setStyle("-fx-background-color: green");
        greenScreen.setVisible(false);

        Label gameOverLabel = new Label("GAME OVER");
        gameOverLabel.setStyle("-fx-font-size: 60; -fx-text-fill: white");

        redScreen.getChildren().add(gameOverLabel);

        gridPane.add(redScreen, 0, 0, GridPane.REMAINING, GridPane.REMAINING);
        gridPane.add(greenScreen, 0, 0, GridPane.REMAINING, GridPane.REMAINING);

        // Create a Pane container for text
        Pane textContainer = new Pane();

        // Create Text nodes for DrillMass and DrillValue
        Text drillMassText = new Text("Drill Mass: " + DrillMass);
        Text drillValueText = new Text("Drill Value: " + DrillValue);
        Text aliEmreARAR = new Text("Created By Ali Emre ARAR");

        aliEmreARAR.setTextAlignment(TextAlignment.RIGHT);
        aliEmreARAR.setFont(Font.font("Times New Roman", 18));
        aliEmreARAR.setFill(Color.WHITE);
        aliEmreARAR.setLayoutY(20);
        aliEmreARAR.setLayoutX(585);
        textContainer.getChildren().add(aliEmreARAR);
        // Set text properties for DrillMassText
        drillMassText.setTextAlignment(TextAlignment.LEFT);
        drillMassText.setFont(Font.font("Arial", 18));
        drillMassText.setFill(Color.WHITE);

        // Set text properties for DrillValueText
        drillValueText.setTextAlignment(TextAlignment.LEFT);
        drillValueText.setFont(Font.font("Arial", 18));
        drillValueText.setFill(Color.WHITE); // Set text color to white

        // Position DrillMassText within the Pane
        drillMassText.setLayoutY(18);
        textContainer.getChildren().add(drillMassText);

        // Position DrillValueText below DrillMassText
        drillValueText.setLayoutY(40);
        textContainer.getChildren().add(drillValueText);

        // Create a Text node for fuel
        Text fuelText = new Text("Fuel: " + fuelValue);

        // Set text properties for fuelText
        fuelText.setTextAlignment(TextAlignment.LEFT);
        fuelText.setFont(Font.font("Arial", 18));
        fuelText.setFill(Color.WHITE); // Set text color to white

        // Position fuelText below drillValueText
        fuelText.setLayoutY(60);
        textContainer.getChildren().add(fuelText);

        // Create a Timeline
        Timeline fuelTimeline = new Timeline();

        // Create a KeyFrame to decrement fuel every 100 milliseconds
        KeyFrame fuelKeyFrame = new KeyFrame(Duration.millis(50), event -> {
            // Decrease fuel
            fuelValue -= 1;

            // Update fuelText content
            fuelText.setText("Fuel: " + fuelValue);
            if (fuelValue<=0){
                Label collectedMoneyLabel = new Label("     GAME OVER\nCollected Money: "+DrillValue);

                collectedMoneyLabel.setStyle("-fx-font-size: 35; -fx-text-fill: white; -fx-font-weight: bold");

                greenScreen.getChildren().add(collectedMoneyLabel);
                greenScreen.setVisible(true);
                greenScreen.toFront();

            }
        });

        // Add KeyFrame to Timeline
        fuelTimeline.getKeyFrames().add(fuelKeyFrame);

        // Set Timeline properties
        fuelTimeline.setCycleCount(Timeline.INDEFINITE);

        // Play Timeline
        fuelTimeline.play();

        // Position the Pane in the top-left corner of the GridPane
        GridPane.setRowIndex(textContainer, 0);
        GridPane.setColumnIndex(textContainer, 0);

        // Add the Pane to the GridPane
        gridPane.getChildren().add(textContainer);


        Scene scene = new Scene(gridPane, 800, 750);
        stage.setScene(scene);
        stage.setTitle("-------------------------------------------------------------------MOTHERLOAD GAME----------------------------------------");


        for (int row = 0; row < 15; row++) {
            for (int col = 0; col < 16; col++) {


                //top of the scene paint blue.
                if (row == 0 || row == 1) {
                    Rectangle blueSquare = new Rectangle(50, 50);
                    blueSquare.setFill(Color.BLUE);
                    gridPane.add(blueSquare, col, row);
                    blueSquare.setId("cell_" + row + "_" + col);

                    //top of the earth put grass.
                } else if (row == 2) {
                    ImageView imageView = new ImageView(top);
                    gridPane.add(imageView, col, row);
                    imageView.setId("cell_" + row + "_" + col);
                    blocks.put("cell_" + row + "_" + col, new Soil(row, col));


                    //put obstacle edge of the scene.
                } else if ((col == 0) || (row == 14) || (col == 15)) {
                    ImageView imageView = new ImageView(obstacle);
                    gridPane.add(imageView, col, row);
                    imageView.setId("cell_" + row + "_" + col);
                    blocks.put("cell_" + row + "_" + col, new Obstacle(row, col));

                    //middle of the scene put randomly blocks.
                } else {
                    Random random = new Random();
                    int randomNumber = random.nextInt(19);
                    ImageView imageView = new ImageView(randomImages.get(randomNumber));
                    gridPane.add(imageView, col, row);
                    imageView.setId("cell_" + row + "_" + col);

                    //create element objects and put them in hashmap.
                    if (randomImages.get(randomNumber) == lava) {
                        blocks.put("cell_" + row + "_" + col, new Lava(row, col));
                    } else if (randomImages.get(randomNumber) == soil) {
                        blocks.put("cell_" + row + "_" + col, new Soil(row, col));
                    } else if (randomImages.get(randomNumber) == obstacle) {
                        blocks.put("cell_" + row + "_" + col, new Obstacle(row, col));
                    } else if (randomImages.get(randomNumber) == amazonite) {
                        blocks.put("cell_" + row + "_" + col, new Amazonite(row, col));
                    } else if (randomImages.get(randomNumber) == emerald) {
                        blocks.put("cell_" + row + "_" + col, new Emerald(row, col));
                    } else if (randomImages.get(randomNumber) == goldium) {
                        blocks.put("cell_" + row + "_" + col, new Goldium(row, col));
                    }else if (randomImages.get(randomNumber) == einsteinium) {
                        blocks.put("cell_" + row + "_" + col, new Einsteinium(row, col));
                    }else if (randomImages.get(randomNumber) == ruby) {
                        blocks.put("cell_" + row + "_" + col, new Ruby(row, col));
                    }else if (randomImages.get(randomNumber) == diamond) {
                        blocks.put("cell_" + row + "_" + col, new Diamond(row, col));
                    }
                }
            }
        }
        //start point of drill
        gridPane.add(imageViewRight, 8, 1);

        scene.addEventFilter(KeyEvent.KEY_PRESSED, key ->{
            switch (key.getCode()) {
                case LEFT:
                    moveDrillLeft(imageViewRight,gridPane,redScreen,drillMassText,drillValueText,fuelText);
                    break;
                case RIGHT:
                    moveDrillRight(imageViewRight,gridPane,redScreen,drillMassText,drillValueText,fuelText);
                    break;
                case UP:
                    moveDrillUp(imageViewRight);
                    break;
                case DOWN:
                    moveDrillDown(imageViewRight,gridPane,redScreen,drillMassText,drillValueText,fuelText);
                    break;
            }
        });

        textContainer.toFront();
        stage.show();
    }
    /**
     * Moves the drill to the left if possible.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     * @param gridPane         The GridPane containing the game grid.
     * @param redScreen        The StackPane for displaying the "GAME OVER" screen.
     * @param drillMassText    The Text node displaying the drill mass.
     * @param drillValueText   The Text node displaying the drill value.
     * @param fuelText         The Text node displaying the fuel value.
     */
    private void moveDrillLeft(ImageView currentImageView,GridPane gridPane,StackPane redScreen,Text drillMassText, Text drillValueText,Text fuelText) {
        int currentColumn = GridPane.getColumnIndex(currentImageView);
        int currentRow = GridPane.getRowIndex(currentImageView);
        int newColumn = currentColumn - 1;

        Image leftDrill = new Image("assets/drill/drill_01.png");
        ImageView imageViewLeft = new ImageView(leftDrill);
        imageViewLeft.setPreserveRatio(true);
        imageViewLeft.setFitWidth(50);
        imageViewLeft.setFitHeight(50);

        //for blue sky
        if (newColumn >= 0) {
            movingControl(currentImageView, gridPane, redScreen, drillMassText, drillValueText, fuelText, currentRow, newColumn, leftDrill);
        }
    }
    /**
     * Moves the drill to the right if possible.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     * @param gridPane         The GridPane containing the game grid.
     * @param redScreen        The StackPane for displaying the "GAME OVER" screen.
     * @param drillMassText    The Text node displaying the drill mass.
     * @param drillValueText   The Text node displaying the drill value.
     * @param fuelText         The Text node displaying the fuel value.
     */
    private void moveDrillRight(ImageView currentImageView,GridPane gridPane,StackPane redScreen,Text drillMassText, Text drillValueText,Text fuelText) {
        int currentColumn = GridPane.getColumnIndex(currentImageView);
        int currentRow = GridPane.getRowIndex(currentImageView);
        int newColumn = currentColumn + 1;

        Image rightDrill = new Image("assets/drill/drill_60.png");
        ImageView imageViewRight = new ImageView(rightDrill);
        imageViewRight.setPreserveRatio(true);
        imageViewRight.setFitWidth(50);
        imageViewRight.setFitHeight(50);

        if (newColumn <= 15) {

            movingControl(currentImageView, gridPane, redScreen, drillMassText, drillValueText, fuelText, currentRow, newColumn, rightDrill);
        }
    }
    /**
     * Moves the drill upward if possible.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     */
    private void moveDrillUp(ImageView currentImageView) {
        int currentRow = GridPane.getRowIndex(currentImageView);
        int newRow = currentRow - 1;
        int currentColumn = GridPane.getColumnIndex(currentImageView);

        Image upDrill = new Image("assets/drill/drill_24.png");
        ImageView imageViewUp = new ImageView(upDrill);
        imageViewUp.setPreserveRatio(true);
        imageViewUp.setFitWidth(50);
        imageViewUp.setFitHeight(50);

        if (newRow >= 0) {

            if (!(blocks.containsKey("cell_" + newRow + "_" + currentColumn))){

                currentImageView.setImage(upDrill);
                GridPane.setRowIndex(currentImageView, newRow);

            }
            Timeline timeline = new Timeline(new KeyFrame(Duration.seconds(2), event -> gravity(currentImageView)));
            timeline.play();
        }
    }
    /**
     * Moves the drill downward if possible.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     * @param gridPane         The GridPane containing the game grid.
     * @param redScreen        The StackPane for displaying the "GAME OVER" screen.
     * @param drillMassText    The Text node displaying the drill mass.
     * @param drillValueText   The Text node displaying the drill value.
     * @param fuelText         The Text node displaying the fuel value.
     */
    private void moveDrillDown(ImageView currentImageView,GridPane gridPane,StackPane redScreen,Text drillMassText, Text drillValueText,Text fuelText) {
        int currentRow = GridPane.getRowIndex(currentImageView);
        int newRow = currentRow + 1;
        int currentColumn = GridPane.getColumnIndex(currentImageView);

        Image downDrill = new Image("assets/drill/drill_44.png");
        ImageView imageViewDown = new ImageView(downDrill);
        imageViewDown.setPreserveRatio(true);
        imageViewDown.setFitWidth(50);
        imageViewDown.setFitHeight(50);

        if (newRow <= 14) {

            if (!(blocks.containsKey("cell_" + newRow + "_" + currentColumn))){

                currentImageView.setImage(downDrill);
                GridPane.setRowIndex(currentImageView, newRow);

            }else {

                if (blocks.get("cell_" + newRow + "_" + currentColumn).isDigging()){

                    removeImageViewWithoutIndexRenumbering(newRow, currentColumn,gridPane);
                    currentImageView.setImage(downDrill);
                    GridPane.setRowIndex(currentImageView, newRow);

                    blockControl(drillMassText, drillValueText, fuelText, newRow, currentColumn);

                }else {
                    if (blocks.get("cell_" + newRow + "_" + currentColumn).isDangerous()){
                        redScreen.setVisible(true);
                        redScreen.toFront();
                    }
                }
            }
            gravity(currentImageView);
        }
    }
    /**
     * Removes an ImageView from the GridPane without renumbering the row and column indices.
     *
     * @param rowIndex    The row index of the ImageView to be removed.
     * @param columnIndex The column index of the ImageView to be removed.
     * @param gridPane    The GridPane containing the ImageView.
     */
    private void removeImageViewWithoutIndexRenumbering(int rowIndex, int columnIndex,GridPane gridPane) {
        int childCount = gridPane.getChildren().size();

        for (int i = 0; i < childCount; i++) {
            Node child = gridPane.getChildren().get(i);
            if (child instanceof ImageView) {
                ImageView imageView = (ImageView) child;

                if (GridPane.getRowIndex(imageView) == rowIndex && GridPane.getColumnIndex(imageView) == columnIndex) {
                    gridPane.getChildren().remove(imageView);
                    return; // Stop iteration after finding and removing the matching ImageView
                }
            }
        }
    }
    /**
     * Controls the movement of the drill based on the specified conditions.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     * @param gridPane         The GridPane containing the game grid.
     * @param redScreen        The StackPane for displaying the "GAME OVER" screen.
     * @param drillMassText    The Text node displaying the drill mass.
     * @param drillValueText   The Text node displaying the drill value.
     * @param fuelText         The Text node displaying the fuel value.
     * @param currentRow       The current row index of the drill.
     * @param newColumn        The new column index to which the drill is moving.
     * @param leftDrill       The Image representing the drill (e.g., leftDrill, rightDrill).
     */
    private void movingControl(ImageView currentImageView, GridPane gridPane, StackPane redScreen, Text drillMassText, Text drillValueText, Text fuelText, int currentRow, int newColumn, Image leftDrill) {
        if (!(blocks.containsKey("cell_" + currentRow + "_" + newColumn))){

            currentImageView.setImage(leftDrill);
            GridPane.setColumnIndex(currentImageView, newColumn);

        }else {

            if (blocks.get("cell_" + currentRow + "_" + newColumn).isDigging()){

                removeImageViewWithoutIndexRenumbering(currentRow, newColumn,gridPane);
                currentImageView.setImage(leftDrill);
                GridPane.setColumnIndex(currentImageView, newColumn);

                blockControl(drillMassText, drillValueText, fuelText, currentRow, newColumn);

            }else {
                if (blocks.get("cell_" + currentRow + "_" + newColumn).isDangerous()){
                    redScreen.setVisible(true);
                    redScreen.toFront();


                }
            }
        }
        gravity(currentImageView);
    }
    /**
     * Controls the behavior of the drill when it encounters a block.
     *
     * @param drillMassText  The Text node displaying the drill mass.
     * @param drillValueText The Text node displaying the drill value.
     * @param fuelText       The Text node displaying the fuel value.
     * @param currentRow     The current row index of the drill.
     * @param newColumn      The new column index where the drill is moving.
     */
    private void blockControl(Text drillMassText, Text drillValueText, Text fuelText, int currentRow, int newColumn) {
        if (blocks.get("cell_" + currentRow + "_" + newColumn).isHasValue()){
            DrillMass += blocks.get("cell_" + currentRow + "_" + newColumn).getMass();
            DrillValue += blocks.get("cell_" + currentRow + "_" + newColumn).getWorth();
            drillMassText.setText("Drill Mass: " + DrillMass);
            drillValueText.setText("Drill Value: " + DrillValue);


        }
        fuelValue -= 100+(DrillMass/10); //fuel value decrease with %1 of the drill mass + 100.
        fuelText.setText("Fuel: " + fuelValue);
        blocks.remove("cell_" + currentRow + "_" + newColumn);
    }
    /**
     * Simulates gravity by moving the drill downward if possible.
     *
     * @param currentImageView The ImageView representing the current position of the drill.
     */
    private void gravity(ImageView currentImageView) {

        Timeline timeline = new Timeline();

        KeyFrame keyFrame = new KeyFrame(Duration.seconds(1), event -> {
            int currentRow = GridPane.getRowIndex(currentImageView);
            int newRow = currentRow + 1;

            if (newRow <= 14) {

                if (!blocks.containsKey("cell_" + newRow + "_" + GridPane.getColumnIndex(currentImageView))) {

                    GridPane.setRowIndex(currentImageView, newRow);
                }
            }
        });
        timeline.getKeyFrames().add(keyFrame);
        timeline.play();
    }
}