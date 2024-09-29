public class Seat {
    private boolean full;
    private double price;
    private final int seatNumber;

    public Seat(int seatNumber) {
        this.seatNumber = seatNumber;
    }
    public boolean isFull() {
        return full;
    }

    public void setFull(boolean full) {
        this.full = full;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public int getSeatNumber() {
        return seatNumber;
    }


}
