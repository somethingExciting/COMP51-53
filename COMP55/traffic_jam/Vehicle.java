import java.util.Arrays;

public class Vehicle {
	boolean isVertical;
	int length;
	Space start;
	VehicleType vType;
	
	public Vehicle(VehicleType v, boolean isVert, int l, int sRow, int sCol) {
		vType = v;
		isVertical = isVert;
		length = l;
		start = new Space(sRow, sCol);
	}
	
	public boolean isVert() {
		return isVertical;
	}
	
	public Space getStart() {
		return start;
	}
	
	public void setStartRow(int row) {
		start.setRow(row);
	}
	
	public void setStartCol(int col) {
		start.setCol(col);
	}
	
	/**
	 * @return the type associated with this particular vehicle
	 */
	public VehicleType getVehicleType() { 
		if(vType.toString() == "car") {
			return VehicleType.MYCAR;
		}
		else if(vType.toString() == "auto") {
			return VehicleType.AUTO;
		}
		return VehicleType.TRUCK;
	}
	
	/**
	 * Provides an array of Spaces that indicate where a particular Vehicle would be located, based on its current starting space
	 * @return the array of Spaces occupied by that particular Vehicles
	 */
	public Space[] spacesOccupied() {	
		Space[] taken = new Space[length];
		int count = 0;
		if(isVertical) {
			int currentRow = start.getRow();
			while(count < length) {
				taken[count] = new Space(currentRow + count, start.getCol());
				count++;
			}
		}
		else {
			int currentCol = start.getCol();
			while(count < length) {
				taken[count] = new Space(start.getRow(), currentCol + count);
				count++;
			}
		}
		return taken;
	}
	
	/**
	 * Calculates an array of the spaces that would be travelled if
	 * a vehicle were to move numSpaces
	 * @param numSpaces The number of spaces to move (can be negative or positive)
	 * @return The array of Spaces that would need to be checked for Vehicles
	 */
	public Space[] spacesOccupiedOnTrail(int numSpaces) {
		Space[] trail = spacesOccupied();
		
		for(int i = 0; i < trail.length; i++) {
			if(isVertical) {
				trail[i].setRow(trail[i].getRow() + numSpaces);
			}
			else {
				trail[i].setCol(trail[i].getCol() + numSpaces);
			}
		}
		return trail;
	}
	
	public static void main(String[] args) {
		//Vehicle(vehicleType, isVert, length, startRow, startCol)
		Vehicle truck1 = new Vehicle(VehicleType.TRUCK, true, 3, 2, 1);
		System.out.print("Vehicle type should be a truck: " + truck1.getVehicleType());
		System.out.println("\nTesting spacesOccupied for a truck: ");
		printSpaces(truck1.spacesOccupied());
		System.out.println("Testing spacesOccupiedOnTrail for a truck: ");
		System.out.print(truck1.spacesOccupiedOnTrail(2) + "\n \n");
		
		Vehicle car1 = new Vehicle(VehicleType.MYCAR, false, 2, 1, 1);
		System.out.print("Vehicle type should be a car: " + car1.getVehicleType());
		System.out.println("\nTesting spacesOccupied for the car: ");
		printSpaces(car1.spacesOccupied());
		System.out.println("Testing spacesOccupiedOnTrail for the car: ");
		System.out.print(car1.spacesOccupiedOnTrail(3) + "\n \n");
		
		Vehicle auto1 = new Vehicle(VehicleType.AUTO, false, 2, 4, 3);
		System.out.print("Vehicle type should be an automobile: " + auto1.getVehicleType());
		System.out.println("\nTesting spacesOccupied for an auto: ");
		printSpaces(auto1.spacesOccupied());
		System.out.println("Testing spacesOccupiedOnTrail for an auto: ");
		System.out.print(auto1.spacesOccupiedOnTrail(4));
	}
	
	public static void printSpaces(Space[] arr) {
		  for(int i = 0; i < arr.length; i++) {
			System.out.print("r" + arr[i].getRow() + "c" + arr[i].getCol() + "; ");	
		  }
		  System.out.println();
		}

}