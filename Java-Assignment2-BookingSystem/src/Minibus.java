/**
 * This is a class representing a Minibus, which extends the abstract Bus class.
 * Each Minibus has an array of Seat objects.
 */
public class Minibus extends Bus{
    public Seat[] seats;
    /**
     * Constructs a new Minibus with the given parameters.
     *
     * @param type The type of the bus
     * @param id The unique ID of the bus
     * @param from The origin of the bus route
     * @param to The destination of the bus route
     * @param rows The number of rows in the bus
     * @param price The price of a ticket for the bus
     */
    public Minibus(String type, int id, String from, String to, int rows, double price) {
        super(type, id, from, to, rows, price);

        seats = new Seat[2*rows];
        for (int i = 0; i < seats.length; i++) {
            seats[i] = new Seat(i+1); // Initialize each slot with a new object
        }
    }
    /**
     * Sells tickets for the given seat numbers and writes the transaction to the given output file.
     *
     * @param seatNumbers The numbers of the seats for which to sell tickets
     * @param outputFile The file to which to write the transaction
     * @return The updated total revenue of the bus after selling the tickets
     */
    @Override
    public double sellTicket( int[] seatNumbers,String outputFile) {
        double totalSoldAmount = 0;

        for (int seatNumber : seatNumbers){
            if (seatNumber<=0){
                FileOutput.writeToFile(outputFile,"ERROR: "+seatNumber+ " is not a positive integer, seat number must be a positive integer!",true,true);
                return getRevenue();

            } else if (!(seatNumber<=seats.length)) {
                FileOutput.writeToFile(outputFile,"ERROR: There is no such a seat!",true,true);
                return getRevenue();
            }
        }
        for (int seatNumber : seatNumbers){
            if (seats[seatNumber-1].isFull()){
                FileOutput.writeToFile(outputFile,"ERROR: One or more seats already sold!",true,true);
                return getRevenue();
            }

        }for (int seatNumber : seatNumbers){
            seats[seatNumber-1].setFull(true);
            seats[seatNumber-1].setPrice(getPrice());
            totalSoldAmount += getPrice();
        }
        setRevenue(getRevenue()+totalSoldAmount);
        FileOutput.writeToFile(outputFile,"Seat "+convertIntArrayToString(seatNumbers)+" of the Voyage "+getId()+" from "+getFrom()+" to "+getTo()+" was successfully sold for "+ String.format("%.2f",totalSoldAmount)+" TL.",true,true);
        return getRevenue();
    }
    /**
     * Attempts to refund tickets for the given seat numbers and writes the transaction to the given output file.
     * However, Minibus tickets are not refundable, so this method always returns an error message.
     *
     * @param seatNumbers The numbers of the seats for which to refund tickets
     * @param outputFile The file to which to write the transaction
     * @return The total revenue of the bus, which is unchanged because the tickets are not refundable
     */
    @Override
    public double refundTicket(int[] seatNumbers,String outputFile) {
        FileOutput.writeToFile(outputFile,"ERROR: Minibus tickets are not refundable!",true,true);
        return getRevenue();
    }

    @Override
    public void printingVoyage(String outputFile) {
        for (Seat seat: seats){
             if (seat.getSeatNumber()%2==0) {

                 if (seat.isFull()){

                     FileOutput.writeToFile(outputFile,"X",true,true);
                 }else {

                     FileOutput.writeToFile(outputFile,"*",true,true);
                 }

            }else {
                if (seat.isFull()){

                    FileOutput.writeToFile(outputFile,"X ",true,false);
                }else {

                    FileOutput.writeToFile(outputFile,"* ",true,false);
                }
            }
        }
    }

    @Override
    public void cancellingVoyage(String outputFile) {
        double totalRefundAmount = 0;
        for (Seat seat: seats){
            if(seat.isFull()){
                totalRefundAmount += getPrice();
            }
        }

        FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",getRevenue()-totalRefundAmount),true,true);

    }

}
