import java.util.*;
/**
 * This is a class representing a BookingSystem.
 * The BookingSystem reads from an input file, writes to an output file, and manages a collection of Bus objects.
 */

public class BookingSystem {
    /**
     * The main method of the BookingSystem class.
     * It reads from an input file specified by the first argument, writes to an output file specified by the second argument,
     * and manages a collection of Bus objects stored in a HashMap.
     *
     * @param args The command-line arguments. The first argument is the name of the input file, and the second argument is the name of the output file.
     */
    public static void main(String[] args) {
        String[] items = FileInput.readFile(args[0], true, true);
        String outputFile = args[1];
        FileOutput.writeToFile(outputFile,"",false,false);

        Map<Integer, Bus> buses = new HashMap<>();

        int lengthOfFile = 0;//for delete newline end of the file

        assert items != null;
        for (String line : items){
            String[] values = line.split("\t");
            lengthOfFile++;

            if (Objects.equals(values[0], "INIT_VOYAGE")){

                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);

                try {int id = Integer.parseInt(values[2]); } catch (Exception e){
                    FileOutput.writeToFile(outputFile,"ERROR: "+ values[2] +" is not a positive integer, ID of a voyage must be a positive integer!",true,true);
                    continue;
                }
                try {int rows = Integer.parseInt(values[5]); } catch (Exception e ){
                    FileOutput.writeToFile(outputFile,"ERROR: "+values[5] +" is not a positive integer, number of seat rows of a voyage must be a positive integer!",true,true);
                    continue;
                }
                try {double price = Double.parseDouble(values[6]); } catch (Exception e ){
                    FileOutput.writeToFile(outputFile,"ERROR: "+values[6]+" is not a positive number, price must be a positive number!",true,true);
                    continue;
                }
                double price = Double.parseDouble(values[6]);
                int id = Integer.parseInt(values[2]);
                int rows = Integer.parseInt(values[5]);
                String type = values[1];
                String from = values[3];
                String to = values[4];

                //error handle part
                if (id<=0){
                    FileOutput.writeToFile(outputFile,"ERROR: "+ id +" is not a positive integer, ID of a voyage must be a positive integer!",true,true);
                    continue;
                }
                if (rows<=0){
                    FileOutput.writeToFile(outputFile,"ERROR: "+rows +" is not a positive integer, number of seat rows of a voyage must be a positive integer!",true,true);
                    continue;
                }
                if (price<=0){
                    FileOutput.writeToFile(outputFile,"ERROR: " +(int)price+" is not a positive number, price must be a positive number!",true,true);
                    continue;
                }

                if (!buses.isEmpty()){
                    if (buses.containsKey(id)) {
                        FileOutput.writeToFile(outputFile,"ERROR: There is already a voyage with ID of " + id + "!",true,true);
                        continue; // Skip to next line after error message
                    }
                }
                // This part of the code is handling the initialization of different types of voyages (Standard, Premium, Minibus)
                if (Objects.equals(values[1],"Standard")){

                    // Try to parse the refund cut value, if it's not a valid integer in the range of [0, 100], write an error message to the output file and skip to the next line
                    try {double refundCut = Double.parseDouble(values[7]); } catch (Exception e ){
                        FileOutput.writeToFile(outputFile,"ERROR: "+values[7]+" is not an integer that is in range of [0, 100], refund cut must be an integer that is in range of [0, 100]!",true,true);
                        continue;
                    }
                    double refundCut = Double.parseDouble(values[7]);

                    // If the refund cut is less than 0 or grater than 100, write an error message to the output file and skip to the next line
                    if (refundCut<0 || refundCut>100){
                        FileOutput.writeToFile(outputFile,"ERROR: "+(int)refundCut+" is not an integer that is in range of [0, 100], refund cut must be an integer that is in range of [0, 100]!",true,true);
                        continue;
                    }
                    // Create a new StandardBus object and add it to the buses map with the id as the key
                    buses.put(id,new StandartBus(type,id,from,to,rows,price,refundCut));
                    FileOutput.writeToFile(outputFile,"Voyage "+id+" was initialized as a standard (2+2) voyage from "+from+" to "+to+" with "+String.format("%.2f",price)+" TL priced "+(4*rows)+" regular seats. Note that refunds will be " +(int)refundCut+"% less than the paid amount.",true,true);

                } else if (Objects.equals(values[1],"Premium")) {
                    // Similar to the "Standard" case, but also includes a premium fee
                    // The rest of the code is similar to the "Standard" case
                    try {double refundCut = Double.parseDouble(values[7]); } catch (Exception e ){
                        FileOutput.writeToFile(outputFile,"ERROR: "+values[7]+" is not an integer that is in range of [0, 100], refund cut must be an integer that is in range of [0, 100]!",true,true);
                        continue;
                    }
                    double refundCut = Double.parseDouble(values[7]);

                    try {double premiumFee = Double.parseDouble(values[8]); } catch (Exception e ){
                        FileOutput.writeToFile(outputFile,"ERROR: "+values[8]+" is not a non-negative integer, premium fee must be a non-negative integer!",true,true);
                        continue;
                    }
                    double premiumFee = Double.parseDouble(values[8]);

                    //error handle
                    if (refundCut<0 || refundCut>100){
                        FileOutput.writeToFile(outputFile,"ERROR: "+(int)refundCut+" is not an integer that is in range of [0, 100], refund cut must be an integer that is in range of [0, 100]!",true,true);
                        continue;
                    }
                    if (premiumFee<0){
                        FileOutput.writeToFile(outputFile,"ERROR: "+(int)premiumFee+" is not a non-negative integer, premium fee must be a non-negative integer!",true,true);
                        continue;
                    }

                    buses.put(id,new PremiumBus(type,id,from,to,rows,price,refundCut,premiumFee));
                    FileOutput.writeToFile(outputFile,"Voyage "+id+" was initialized as a premium (1+2) voyage from "+from+" to "+to+" with "+String.format("%.2f",price)+" TL priced "+2*rows+" regular seats and "+String.format("%.2f",(100+premiumFee)/100*price)+" TL priced "+rows+" premium seats. Note that refunds will be "+(int)refundCut+"% less than the paid amount.",true,true);

                } else if (Objects.equals(values[1],"Minibus")) {
                    // For a "Minibus" voyage, there is no refund cut or premium fee
                    // Create a new Minibus object and add it to the buses map with the id as the key
                    buses.put(id,new Minibus(type,id,from,to,rows,price));
                    FileOutput.writeToFile(outputFile,"Voyage "+id+" was initialized as a minibus (2) voyage from "+from+" to "+to+" with "+String.format("%.2f",price)+" TL priced "+(2*rows)+" regular seats. Note that minibus tickets are not refundable.",true,true);

                }else {
                    // If the voyage type is not "Standard", "Premium", or "Minibus", write an error message to the output file
                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"INIT_VOYAGE\" command!",true,true);

                }
                // This part of the code is handling the selling of tickets, refunding of tickets, and printing of voyage details
            } else if (Objects.equals(values[0], "SELL_TICKET")) {

                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                if (values.length !=3){
                    // If the command does not have the correct number of arguments, write an error message to the output file
                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"SELL_TICKET\" command!",true,true);

                }else {
                    // If the bus with the given ID exists, sell the ticket
                    int id = Integer.parseInt(values[1]);
                    if (buses.containsKey(id)){
                        buses.get(id).sellTicket(convertToIntArray(values[2]),outputFile);

                    }else {
                        // If the bus with the given ID does not exist, write an error message to the output file
                        FileOutput.writeToFile(outputFile,"ERROR: There is no voyage with ID of "+id+"!",true,true);
                    }
                }
            } else if (Objects.equals(values[0],"REFUND_TICKET")) {
                // Similar to the "SELL_TICKET" case, but for refunding tickets

                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                if (values.length !=3){
                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"REFUND_TICKET\" command!",true,true);

                }else {
                    // If the bus with the given ID exists, print the voyage details
                    int id = Integer.parseInt(values[1]);
                    if (buses.containsKey(id)){

                        buses.get(id).refundTicket(convertToIntArray(values[2]), outputFile);

                    }else {
                        // If the bus with the given ID does not exist, write an error message to the output file
                        FileOutput.writeToFile(outputFile,"ERROR: There is no voyage with ID of "+id+"!",true,true);
                    }
                }
            } else if (Objects.equals(values[0],"PRINT_VOYAGE")) {
                // This part of the code is handling the printing of voyage details and cancellation of voyages

                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                // If the command does not have the correct number of arguments, write an error message to the output file
                if (values.length !=2){
                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"PRINT_VOYAGE\" command!",true,true);

                }else {
                    // If the bus with the given ID exists, print the voyage details
                    int id = Integer.parseInt(values[1]);
                    if (id<=0){
                        FileOutput.writeToFile(outputFile,"ERROR: "+id +" is not a positive integer, ID of a voyage must be a positive integer!",true,true);
                        continue;
                    }
                    if (buses.containsKey(id)){

                        FileOutput.writeToFile(outputFile,"Voyage "+id,true,true);
                        FileOutput.writeToFile(outputFile,buses.get(id).getFrom()+"-"+buses.get(id).getTo(),true,true);
                        buses.get(id).printingVoyage(outputFile);
                        FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",buses.get(id).getRevenue()),true,true);


                    }else {
                        // If the bus with the given ID does not exist, write an error message to the output file
                        FileOutput.writeToFile(outputFile,"ERROR: There is no voyage with ID of "+id+"!",true,true);
                    }
                }
            } else if (Objects.equals(values[0],"CANCEL_VOYAGE")) {

                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                if (values.length !=2){
                    // If the command does not have the correct number of arguments, write an error message to the output file
                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"CANCEL_VOYAGE\" command!",true,true);

                }else {
                    // If the bus with the given ID exists, cancel the voyage and remove the bus from the buses map
                    int id = Integer.parseInt(values[1]);
                    if (id<=0){
                        FileOutput.writeToFile(outputFile,"ERROR: "+ id +" is not a positive integer, ID of a voyage must be a positive integer!",true,true);
                        continue;
                    }
                    if (buses.containsKey(id)){

                        FileOutput.writeToFile(outputFile,"Voyage "+id+" was successfully cancelled!",true,true);
                        FileOutput.writeToFile(outputFile,"Voyage details can be found below:",true,true);
                        FileOutput.writeToFile(outputFile,"Voyage "+id,true,true);
                        FileOutput.writeToFile(outputFile,buses.get(id).getFrom()+"-"+buses.get(id).getTo(),true,true);
                        buses.get(id).printingVoyage(outputFile);
                        buses.get(id).cancellingVoyage(outputFile);  //print revenue after refund ticket
                        buses.remove(id);


                    }else {
                        // If the bus with the given ID does not exist, write an error message to the output file
                        FileOutput.writeToFile(outputFile,"ERROR: There is no voyage with ID of "+id+"!",true,true);
                    }
                }
                // This part of the code is handling the generation of Z reports and cancellation of voyages
            }else if (Objects.equals(values[0],"Z_REPORT")){
                // Write the command to the output file
                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                if (values.length != 1){
                    // If the command does not have the correct number of arguments, write an error message to the output file

                    FileOutput.writeToFile(outputFile,"ERROR: Erroneous usage of \"Z_REPORT\" command!",true,true);

                }else {
                    // If the last command in the input file is "Z_REPORT" and the current line is the last line of the file, generate a Z report
                    if ((Objects.equals(items[items.length-1].split("\t")[0], "Z_REPORT")) && (lengthOfFile== items.length)){
                        FileOutput.writeToFile(outputFile,"Z Report:",true,true);
                        FileOutput.writeToFile(outputFile,"----------------",true,true);

                        if (!buses.isEmpty()){
                            int sayac = 0;
                            for (int idForZReport : buses.keySet()){
                                sayac++;
                                FileOutput.writeToFile(outputFile,"Voyage "+idForZReport,true,true);
                                FileOutput.writeToFile(outputFile,buses.get(idForZReport).getFrom()+"-"+buses.get(idForZReport).getTo(),true,true);
                                buses.get(idForZReport).printingVoyage(outputFile);
                                FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",buses.get(idForZReport).getRevenue()),true,true);

                                if (sayac== buses.size()){

                                    FileOutput.writeToFile(outputFile,"----------------",true,false);
                                }else {

                                    FileOutput.writeToFile(outputFile,"----------------",true,true);
                                }
                            }
                        }else {
                            FileOutput.writeToFile(outputFile,"No Voyages Available!",true,true);
                            FileOutput.writeToFile(outputFile,"----------------",true,false);
                        }

                    }else {
                        FileOutput.writeToFile(outputFile,"Z Report:",true,true);
                        FileOutput.writeToFile(outputFile,"----------------",true,true);

                        if (!buses.isEmpty()){
                            for (int idForZReport : buses.keySet()){
                                FileOutput.writeToFile(outputFile,"Voyage "+idForZReport,true,true);
                                FileOutput.writeToFile(outputFile,buses.get(idForZReport).getFrom()+"-"+buses.get(idForZReport).getTo(),true,true);
                                buses.get(idForZReport).printingVoyage(outputFile);
                                FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",buses.get(idForZReport).getRevenue()),true,true);
                                FileOutput.writeToFile(outputFile,"----------------",true,true);
                            }

                        }else {
                            FileOutput.writeToFile(outputFile,"No Voyages Available!",true,true);
                            FileOutput.writeToFile(outputFile,"----------------",true,true);
                        }
                    }
                }
                //if input include error command this block works
            }else{
                String error = values[0];
                FileOutput.writeToFile(outputFile,"COMMAND: "+line,true,true);
                FileOutput.writeToFile(outputFile,"ERROR: There is no command namely "+error+"!",true,true);
            }
        }
        if (!Objects.equals(items[items.length-1].split("\t")[0], "Z_REPORT")){

            FileOutput.writeToFile(outputFile,"Z Report:",true,true);
            FileOutput.writeToFile(outputFile,"----------------",true,true);

            if (!buses.isEmpty()){
                int sayac = 0;
                for (int idForZReport : buses.keySet()){
                    sayac++;
                    FileOutput.writeToFile(outputFile,"Voyage "+idForZReport,true,true);
                    FileOutput.writeToFile(outputFile,buses.get(idForZReport).getFrom()+"-"+buses.get(idForZReport).getTo(),true,true);
                    buses.get(idForZReport).printingVoyage(outputFile);
                    FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",buses.get(idForZReport).getRevenue()),true,true);

                    if (sayac== buses.size()){

                        FileOutput.writeToFile(outputFile,"----------------",true,false);
                    }else {

                        FileOutput.writeToFile(outputFile,"----------------",true,true);
                    }
                }
            }else {
                FileOutput.writeToFile(outputFile,"No Voyages Available!",true,true);
                FileOutput.writeToFile(outputFile,"----------------",true,false);
            }
        }
    }
    /**
     * Converts a string of numbers separated by underscores ("_") into an array of integers.
     *
     * @param input The string of numbers to convert. Numbers should be separated by underscores ("_").
     * @return An array of integers parsed from the input string.
     */
    public static int[] convertToIntArray(String input) {

        String[] strNumbers;
        if (input.contains("_")) {
            // Handle comma-separated string
            strNumbers = input.split("_");
        } else {
            // Handle single number
            strNumbers = new String[]{input};
        }

        int[] intArray = new int[strNumbers.length];
        for (int i = 0; i < strNumbers.length; i++) {
            intArray[i] = Integer.parseInt(strNumbers[i]);
        }
        return intArray;
    }
}



