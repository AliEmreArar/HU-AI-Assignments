public class Main {
    /**
     * The main method of the application.
     * It takes in three arguments: the file paths for the product information, purchase information, and output file.
     * It creates a GMM, fills it with products, prints the inventory, processes the purchases, and prints the final inventory.
     *
     * @param args The command line arguments. args[0] is the product information file, args[1] is the purchase information file, and args[2] is the output file.
     */
    public static void main(String[] args) {
        String[] content = FileInput.readFile(args[0], true, true);
        String[] purchase = FileInput.readFile(args[1], true, true);

        String outputFile = args[2];
        FileOutput.writeToFile(outputFile,"",false,false);

        GMM gmm = new GMM();
        assert content != null;
        gmm.fill(content,outputFile);
        FileOutput.writeToFile(outputFile,"-----Gym Meal Machine-----",true,true);
        gmm.printInventory(outputFile);
        FileOutput.writeToFile(outputFile,"----------",true,true);
        assert purchase != null;
        gmm.buyProduct(purchase,outputFile);
        FileOutput.writeToFile(outputFile,"-----Gym Meal Machine-----",true,true);
        gmm.printInventory(outputFile);
        FileOutput.writeToFile(outputFile,"----------",true,true);

    }
}
