/**
 * This is a class representing a PremiumBus, which extends the abstract Bus class.
 * Each PremiumBus has a refund cut percentage and a premium fee percentage in addition to the properties of a Bus.
 * It also contains an array of Seat objects.
 */
public class PremiumBus extends Bus{
    private final double refundCut;
    private final double premiumFee;
    public Seat[] seats;
    /**
     * Constructs a new PremiumBus with the given parameters.
     *
     * @param type The type of the bus
     * @param id The unique ID of the bus
     * @param from The origin of the bus route
     * @param to The destination of the bus route
     * @param rows The number of rows in the bus
     * @param price The price of a ticket for the bus
     * @param refundCut The percentage of the ticket price that is refunded when a ticket is refunded
     * @param premiumFee The additional fee charged for premium seats
     */
    public PremiumBus(String type, int id, String from, String to, int rows, double price, double refundCut, double premiumFee) {
        super(type, id, from, to, rows, price);
        this.refundCut = refundCut;
        this.premiumFee = premiumFee;

        seats = new Seat[3*rows];
        for (int i = 0; i < seats.length; i++) {
            seats[i] = new Seat(i+1); // Initialize each slot with a new object
        }
    }
    /**
     * Sells tickets for the given seat numbers and writes the transaction to the given output file.
     * Premium seats (those with a seat number that is a multiple of 3) have a premium fee added to the ticket price.
     *
     * @param seatNumbers The numbers of the seats for which to sell tickets
     * @param outputFile The file to which to write the transaction
     * @return The updated total revenue of the bus after selling the tickets
     */
    @Override
    public double sellTicket(int[] seatNumbers,String outputFile) {
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
            if (seatNumber%3==1){
                seats[seatNumber-1].setFull(true);
                seats[seatNumber-1].setPrice((100+premiumFee)/100*getPrice());
                totalSoldAmount += ((100+premiumFee)/100*getPrice());

            }else {
                seats[seatNumber-1].setFull(true);
                seats[seatNumber-1].setPrice(getPrice());
                totalSoldAmount += getPrice();
            }
        }
        setRevenue(getRevenue()+totalSoldAmount);
        FileOutput.writeToFile(outputFile,"Seat "+convertIntArrayToString(seatNumbers)+" of the Voyage "+getId()+" from "+getFrom()+" to "+getTo()+" was successfully sold for "+String.format("%.2f",totalSoldAmount)+" TL.",true,true);
        return getRevenue();
    }
    /**
     * Refunds tickets for the given seat numbers and writes the transaction to the given output file.
     * Only a portion of the ticket price (determined by the refund cut) is refunded.
     *
     * @param seatNumbers The numbers of the seats for which to refund tickets
     * @param outputFile The file to which to write the transaction
     * @return The updated total revenue of the bus after refunding the tickets
     */
    @Override
    public double refundTicket(int[] seatNumbers,String outputFile) {
        double totalRefundAmount = 0;

        for (int seatNumber : seatNumbers){
            if (seatNumber<=0){
                FileOutput.writeToFile(outputFile,"ERROR: "+seatNumber+ " is not a positive integer, seat number must be a positive integer!",true,true);
                return getRevenue();

            } else if (!(seatNumber<=seats.length)) {
                FileOutput.writeToFile(outputFile,"ERROR: There is no such a seat!",true,true);
                return getRevenue();
            }
        }
        for (int seatNumber : seatNumbers) {
            if (!seats[seatNumber-1].isFull()) {
                FileOutput.writeToFile(outputFile,"ERROR: One or more seats are already empty!",true,true);
                return getRevenue();
            }
        }for (int seatNumber : seatNumbers){
            if (seatNumber%3==1){
                seats[seatNumber-1].setFull(false);
                seats[seatNumber-1].setPrice(((100+premiumFee)/100*getPrice())*refundCut/100);
                totalRefundAmount += (((100+premiumFee)/100*getPrice())*(100-refundCut)/100);

            }else {
                seats[seatNumber-1].setFull(false);
                seats[seatNumber-1].setPrice(getPrice()*refundCut/100);
                totalRefundAmount +=(getPrice()*(100-refundCut)/100);
            }
        }
        setRevenue(getRevenue()-totalRefundAmount);
        FileOutput.writeToFile(outputFile,"Seat "+convertIntArrayToString(seatNumbers)+" of the Voyage "+getId()+" from "+getFrom()+" to "+getTo()+" was successfully refunded for "+String.format("%.2f",totalRefundAmount)+" TL.",true,true);
        return getRevenue();
    }

    @Override
    public void printingVoyage(String outputFile) {
        for (Seat seat: seats){
            if (seat.getSeatNumber()%3==1){
                if (seat.isFull()){
                    FileOutput.writeToFile(outputFile,"X | ",true,false);
                }else {
                    FileOutput.writeToFile(outputFile,"* | ",true,false);
                }

            } else if (seat.getSeatNumber()%3==0) {

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
                if (seat.getSeatNumber()%3==1){
                    totalRefundAmount += ((100+premiumFee)/100*getPrice());
                }else {
                    totalRefundAmount += getPrice();
                }
            }
        }
        FileOutput.writeToFile(outputFile,String.format("Revenue: %.2f",getRevenue()-totalRefundAmount),true,true);
    }
}
