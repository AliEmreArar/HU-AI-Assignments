import java.util.Objects;

public class GMM {
    public Slot[] slots;

    public GMM() {
        slots = new Slot[24];
        for (int i = 0; i < slots.length; i++) {
            slots[i] = new Slot(); // Initialize each slot with a new object
        }

    }
    /**
     * This method fills the slots with the products provided in the content array.
     * It iterates over each line in the content, splits the line into parts and creates a new product.
     * If a slot is empty or contains the same product and is not full, the product is added to the slot.
     * If no suitable slot is found, it writes an info message to the output file.
     * If the machine is full, it writes an info message to the output file and returns -1.
     *
     * @param content An array containing the information of the products to be added.
     * @param outputFile The name of the file where the info messages will be written.
     * @return If the operation is successful, it returns 0, otherwise -1.
     */
    public int fill(String[] content,String outputFile){
        // Iterate over each line in the content
        for(String line : content){

            int temp = 0;

            // Split the line into parts
            String[] parts = line.split("\t");
            // Split the third part into values
            String[] values = parts[2].split(" ");
            String name = parts[0];
            int price = Integer.parseInt(parts[1]);
            double protein = Double.parseDouble(values[0]);
            double carbohydrate = Double.parseDouble(values[1]);
            double fat = Double.parseDouble(values[2]);

            // Iterate over each slot
            for (int i = 0; i < slots.length; i++) {
                // If the slot is empty, add the product directly
                if (slots[i].getNumber() ==0){
                    slots[i] = new Slot(name,price,protein,carbohydrate,fat);
                    slots[i].addProduct();
                    temp = 1;
                    break;
                } else {
                    // If the slot is not empty and has the same name, add the product
                    if(slots[i].getNumber()<10 && Objects.equals(slots[i].getName(), name)){
                        slots[i].addProduct();
                        temp = 1;
                        break;
                    }

                }

            }
            // If no suitable slot was found, write to file
            if (temp ==0){

                FileOutput.writeToFile(outputFile,"INFO: There is no available place to put "+name,true,true);
                int totalProductNum = 0;
                for (Slot slot : slots) {
                    totalProductNum += slot.getNumber();
                    // If the machine is full, write to file and return -1
                    if (totalProductNum == 240) {

                        FileOutput.writeToFile(outputFile,"INFO: The machine is full!",true,true);
                        return -1;
                    }
                }
            }

        }

        return 0;
    }
    /**
     * This method prints the inventory of slots to a specified output file.
     * It iterates over each slot and writes the product details to the file.
     * If a slot is empty, it writes a placeholder. After every 4 slots, it adds a new line.
     *
     * @param outputFile The name of the file where the inventory will be written.
     */
    public void printInventory(String outputFile) {

        // Iterate over each slot
        for (int i = 0; i < slots.length; i++) {
            Slot slot = slots[i];
            // If the slot is empty, write to file
            if (slot.getNumber()==0) {

                FileOutput.writeToFile(outputFile,"___(0, 0)___",true,false);
            }else {
                // If the slot is not empty, write the product details to file
                FileOutput.writeToFile(outputFile,slot.getName() + "(" + slot.getCalorie() + ", " + slot.getNumber() + ")___",true,false);
            }
            // Add a new line after every 4 slots
            if (i==3 || i==7 || i==11 || i==15 || i==19 || i==23){

                FileOutput.writeToFile(outputFile,"",true,true);

            }
        }
    }

    /**
     * This method purchases a product based on a specific type and quantity range.
     * If there is enough money and the desired product is available, the product is purchased and the change is returned.
     * If there is not enough money or the desired product is not available, the money is refunded.
     *
     * @param purchase An array containing the information of the products to be purchased.
     * @param outputFile The name of the file where the outputs will be written.
     * @return If the operation is successful, it returns 0, otherwise -1.
     */
    public int buyProduct(String[] purchase,String outputFile){
        // Iterate over each line in the purchase
        for(String line : purchase){
            int money = 0;
            int temp = 0;

            // Split the line into parts
            String[] parts = line.split("\t");
            // If the second part is not a single character, split it into cents

            // Write the input to the file
            FileOutput.writeToFile(outputFile,"INPUT: "+line,true,true);

            if (parts[1].length()!=1){
                String[] cents = parts[1].split(" ");
                // Convert each cent into lira and add to the total money
                for (String i : cents){
                    int lira = Integer.parseInt(i);

                    if (lira == 1 || lira == 5 || lira == 10 || lira == 20 || lira == 50 || lira == 100 || lira == 200){
                        money += lira;
                    }else {
                        FileOutput.writeToFile(outputFile,"INFO: Invalid money!",true,true);

                    }
                }if (money == 0){
                    FileOutput.writeToFile(outputFile,"RETURN: Returning your change: 0 TL",true,true);
                    continue;
                }
            }else {
                // If the second part is a single character, convert it directly into money
                money = Integer.parseInt(parts[1]);
                if (!(money == 1 || money == 5 || money == 10 || money == 20 || money == 50 || money == 100 || money == 200)) {
                    FileOutput.writeToFile(outputFile,"INFO: Invalid money!",true,true);
                    FileOutput.writeToFile(outputFile,"RETURN: Returning your change: 0 TL",true,true);
                    continue;
                }
            }
            String type = parts[2];
            double amount = Double.parseDouble(parts[3]);

            // If the type is "NUMBER"
            if (Objects.equals(type,"NUMBER")){
                // If the amount is within the valid range
                if ((int)amount>=0 && (int)amount<=23){
                    // If the slot is not empty
                    if (slots[(int)amount].getNumber()>0){
                        // If the money is enough to buy the product
                        if (money>=slots[(int)amount].getPrice()){
                            // Write the purchase and return information to the file
                            FileOutput.writeToFile(outputFile,"PURCHASE: You have bought one "+slots[(int)amount].getName(),true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money-slots[(int)amount].getPrice())+" TL",true,true);
                            // Delete the product from the slot
                            slots[(int)amount].delProduct();

                            continue;
                        }
                    }else {
                        // If the slot is empty, write the information to the file and return the money
                        FileOutput.writeToFile(outputFile,"INFO: This slot is empty, your money will be returned.",true,true);
                        FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);

                        continue;
                    }
                }else {
                    // If the number is not accepted, write the information to the file and return the money
                    FileOutput.writeToFile(outputFile,"INFO: Number cannot be accepted. Please try again with another number.",true,true);
                    FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);

                    continue;
                }


            }

            for (Slot slot : slots) {
                // If the type is "CARB"
                if (Objects.equals(type, "CARB")) {
                    // If the carbohydrate content of the slot is within the desired range and the slot is not empty
                    if ((amount - 5) <= slot.getCarbohydrate() && slot.getCarbohydrate() <= (amount + 5) && slot.getNumber()>0) {
                        // If the money is enough to buy the product
                        if (money >= slot.getPrice()) {
                            // Write the purchase and return information to the file
                            FileOutput.writeToFile(outputFile,"PURCHASE: You have bought one " + slot.getName(),true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: " + (money-slot.getPrice()) + " TL",true,true);
                            // Delete the product from the slot
                            slot.delProduct();
                            temp = 1;
                        } else {
                            // If the money is not enough, write the information to the file and return the money
                            FileOutput.writeToFile(outputFile,"INFO: Insufficient money, try again with more money.",true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);
                            temp = 1;
                        }
                        break;
                    }
                } else if (Objects.equals(type, "PROTEIN")) {
                    // If the protein content of the slot is within the desired range and the slot is not empty
                    if ((amount - 5) <= slot.getProtein() && slot.getProtein() <= (amount + 5)&& slot.getNumber()>0) {
                        // If the money is enough to buy the product
                        if (money >= slot.getPrice()) {
                            // Write the purchase and return information to the file
                            FileOutput.writeToFile(outputFile,"PURCHASE: You have bought one " + slot.getName(),true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: " + (money-slot.getPrice()) + " TL",true,true);
                            // Delete the product from the slot
                            slot.delProduct();
                            temp = 1;
                        } else {
                            // If the money is not enough, write the information to the file and return the money
                            FileOutput.writeToFile(outputFile,"INFO: Insufficient money, try again with more money.",true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);
                            temp = 1;
                        }
                        break;
                    }

                } else if (Objects.equals(type, "FAT")) {
                    // If the type is "FAT"
                    // If the fat content of the slot is within the desired range and the slot is not empty
                    if ((amount - 5) <= slot.getFat() && slot.getFat() <= (amount + 5)&& slot.getNumber()>0) {
                        // If the money is enough to buy the product
                        if (money >= slot.getPrice()) {
                            // Write the purchase and return information to the file
                            FileOutput.writeToFile(outputFile,"PURCHASE: You have bought one " + slot.getName(),true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: " + (money-slot.getPrice()) + " TL",true,true);
                            // Delete the product from the slot
                            slot.delProduct();
                            temp = 1;
                        } else {
                            // If the money is not enough, write the information to the file and return the money
                            FileOutput.writeToFile(outputFile,"INFO: Insufficient money, try again with more money.",true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);
                            temp = 1;
                        }
                        break;
                    }

                } else if (Objects.equals(type, "CALORIE")){
                    // If the type is "CALORIE"
                    // If the calorie content of the slot is within the desired range and the slot is not empty
                    if ((amount - 5) <= slot.getCalorie() && slot.getCalorie() <= (amount + 5)&& slot.getNumber()>0) {
                        // If the money is enough to buy the product
                        if (money >= slot.getPrice()) {
                            // Write the purchase and return information to the file
                            FileOutput.writeToFile(outputFile,"PURCHASE: You have bought one " + slot.getName(),true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: " + (money-slot.getPrice()) + " TL",true,true);
                            // Delete the product from the slot
                            slot.delProduct();
                            temp = 1;
                        } else {
                            // If the money is not enough, write the information to the file and return the money
                            FileOutput.writeToFile(outputFile,"INFO: Insufficient money, try again with more money.",true,true);
                            FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);
                            temp = 1;
                        }
                        break;
                    }

                }
            // If no suitable product was found, write the information to the file and return the money
            }if (temp==0){

                FileOutput.writeToFile(outputFile,"INFO: Product not found, your money will be returned.",true,true);
                FileOutput.writeToFile(outputFile,"RETURN: Returning your change: "+(money)+" TL",true,true);

            }
        }
        return -1;
    }

}