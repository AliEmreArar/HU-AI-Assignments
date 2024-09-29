/**
 * This class represents a Slot in a vending machine.
 * Each Slot has a name, price, protein, carbohydrate, fat content, and number of items.
 */
public class Slot {
    private String name;
    private int price;
    private double protein;
    private double carbohydrate;
    private double fat;
    private int number;

    /**
     * Default constructor for Slot.
     */
    public Slot(){

    }

    /**
     * Constructor for Slot with parameters.
     * @param name The name of the product in the slot.
     * @param price The price of the product in the slot.
     * @param protein The protein content of the product in the slot.
     * @param carbohydrate The carbohydrate content of the product in the slot.
     * @param fat The fat content of the product in the slot.
     */
    public Slot(String name, int price, double protein, double carbohydrate, double fat){
        this.setName(name);
        this.setCarbohydrate(carbohydrate);
        this.setFat(fat);
        this.setPrice(price);
        this.setProtein(protein);
    }

    /**
     * Method to add a product to the slot.
     */
    public void addProduct(){
        setNumber(getNumber() + 1);
    }

    /**
     * Method to remove a product from the slot.
     */
    public void delProduct(){
        setNumber(getNumber() - 1);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    public double getProtein() {
        return protein;
    }

    public void setProtein(double protein) {
        this.protein = protein;
    }

    public double getCarbohydrate() {
        return carbohydrate;
    }

    public void setCarbohydrate(double carbohydrate) {
        this.carbohydrate = carbohydrate;
    }

    public double getFat() {
        return fat;
    }

    public void setFat(double fat) {
        this.fat = fat;
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    /**
     * Method to calculate the calorie content of the product in the slot.
     * @return The calorie content of the product.
     */
    public int getCalorie() {
        return (int) Math.round((4 * protein) + (4 * carbohydrate) + (9 * fat));

    }


}