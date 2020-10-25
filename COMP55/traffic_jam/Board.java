import java.util.*;

/**
 * This represents the board.  Really what it is going to do is just have an array of the vehicles
 * on the board, and it will be in charge of doing the bounds type checking for doing any of the moves.
 * It will also have a method display board which will give back a string representation of the board
 * 
 * @author Melissa Chow
 *
 */

public class Board {
	Vehicle[][] board;

	
	//TODO Add the other methods that are in the handout, and fill out the rest of this file
	
	/**
	 * Constructor for the board which sets up an empty board of size rows by columns
	 * Use the first array index as the rows and the second index as the columns
	 * 
	 * @param rows number of rows on the board
	 * @param cols number of columns on the board
	 */
	public Board(int rows, int cols) {
		board = new Vehicle[rows][cols];
	}
	
	/**
	 * @return number of columns the board has
	 */
	public int getNumCols() {
		return board[0].length;
	}

	/**
	 * @return number of rows the board has
	 */
	public int getNumRows() {
		return board.length;
	}

	/**
	 * Grabs the vehicle present on a particular space if any is there
	 * If a Vehicle occupies three spaces, the same Vehicle pointer should be returned for all three spaces
	 * 
	 * @param s the desired space where you want to look to see if a vehicle is there
	 * @return a pointer to the Vehicle object present on that space, if no Vehicle is present, null is returned
	 */
	public Vehicle getVehicle(Space s) {
		if(board[s.getRow()][s.getCol()] != null) {
			return board[s.getRow()][s.getCol()];
		}
		else {
			return null;
		}
		
	}
	
	public ArrayList<Vehicle> getAllVehicles() {
		ArrayList<Vehicle> vehicles = new ArrayList<Vehicle>();
		for(int i = 0; i < getNumRows(); i++) {
			for(int j = 0; j < getNumCols(); j++) {
				if(board[i][j] == null && !vehicles.contains(getVehicle(new Space(i,j)))) {
					vehicles.add(getVehicle(new Space(i,j)));
				}
			}
		}
		return vehicles;
	}

	/**
	 * adds a vehicle to the board. It would be good to do some checks for a legal placement here.
	 * 
	 * @param type type of the vehicle
	 * @param startRow row for location of vehicle's top
	 * @param startCol column for for location of vehicle leftmost space
	 * @param numSpaces number of spaces the vehicle occupies on the board
	 * @param vert true if the vehicle should be vertical
	 */
	public void addVehicle(VehicleType type, int startRow, int startCol, int numSpaces, boolean vert) {
		Vehicle v = new Vehicle(type, vert, numSpaces, startRow, startCol);
		Space[] t = v.spacesOccupied();
		
		if(vert) {
			for(int i = 0; i < t.length; i++) {
				if(board[t[i].getRow()][t[i].getCol()] == null) {
					board[t[i].getRow()][t[i].getCol()] = v;
				}
			}
			return;
		}
		for(int i = 0; i < t.length; i++) {
			if(board[t[i].getRow()][t[i].getCol()] == null) {
				board[t[i].getRow()][t[i].getCol()] = v;
			}
		}
		return;
	}

	/**
	 * This method moves the vehicle on a certain row/column a specific number of spaces
	 * 
	 * @param start the starting row/column of the vehicle in question
	 * @param numSpaces the number of spaces to be moved by the vehicle (can be positive or negative)
	 * @return whether or not the move actually happened
	 */
	public boolean moveNumSpaces(Space start, int numSpaces) {
		//this function moves the car and returns true/false if it moved
		Vehicle v = getVehicle(start);
		
		if(canMoveNumSpaces(start, numSpaces)) {
			Space[] current = v.spacesOccupied();
			Space[] update = v.spacesOccupiedOnTrail(numSpaces);
			
			for(int i = 0; i < update.length; i++) {
				board[current[i].getRow()][current[i].getCol()] = null;
				board[update[i].getRow()][update[i].getCol()] = v;
			}
			return true;
		}
		return false;
	}
	
	/**
	 * This method just checks to see if the vehicle on a certain row/column can move a specific number of spaces, though
	 * it will not move the vehicle.  You should use this when you wish to move or want to see if you can
	 * move a vehicle numSpaces without going out of bounds or hitting another vehicle
	 * 
	 * @param start the starting row/column of the vehicle in question
	 * @param numSpaces number of spaces to be moved by the vehicle (positive or negative)
	 * @return whether or not the move is possible
	 */
	public boolean canMoveNumSpaces(Space start, int numSpaces) {
		//this function checks to see if a certain move is possible
		Vehicle v = getVehicle(start);
		
		//if the space being checked is not occupied with a vehicle
		if(v == null) {
			return false;
		}
		//if the move exceeds the row limit of the board
		if((start.getRow() + numSpaces > 5) || (start.getRow() + numSpaces < 0)) {
			return false;
		}
		//if the move exceeds the column limit of the board
		if((start.getCol() + numSpaces >= 5) || (start.getCol() + numSpaces < 0)) {
			return false;
		}
		//checking if the spaces on the vehicle's trail are being occupied
		Space[] t = v.spacesOccupiedOnTrail(numSpaces);
		for(int i = 0; i < t.length - 2; i++) {
			if(t[i] != null && getVehicle(t[i]) != v) {
				return false;
			}
		}
		return true;
	}
	
	public void clearBoard() {
		for(int i = 0; i < getNumRows(); i++) {
			for(int j = 0; j < getNumCols(); j++) {
				board[i][j] = null;
			}
		}
	}
	
	// This method helps create a string version of the board
	// You do not need to call this at all, just let it be
	public String toString() {
		return BoardConverter.createString(this);
	}
	
	/* Testing methods down here for testing the board 
	 * make sure you run the board and it works before you write the rest of the program! */
	
	public static void main(String[] args) {
		Board b = new Board(5, 5);
		b.addVehicle(VehicleType.MYCAR, 1, 0, 2, false);
		b.addVehicle(VehicleType.TRUCK, 0, 2, 3, true);
		b.addVehicle(VehicleType.AUTO, 3, 3, 2, true);
		b.addVehicle(VehicleType.AUTO, 0, 3, 2, true);
		System.out.println(b);
		testCanMove(b);
		testMoving(b);
		System.out.println(b);
	}
	
	public static void testMoving(Board b) {
		System.out.println("just moving some stuff around");
		b.moveNumSpaces(new Space(1, 2), 1);
		b.moveNumSpaces(new Space(1, 2), 1);
		b.moveNumSpaces(new Space(1, 1), 1);
	}
	
	public static void testCanMove(Board b) {
		System.out.println("Ok, now testing some moves...");
		System.out.println("These should all be true");
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(0, 2), 2));
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(1, 2), 2));
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(2, 2), 2));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(3, 3), -1));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(4, 3), -1));
		
		System.out.println("\nAnd these should all be false");
		System.out.println("Moving truck down " + b.canMoveNumSpaces(new Space(3, 2), 2));
		System.out.println("Moving the car into truck" + b.canMoveNumSpaces(new Space(2, 0), 1));
		System.out.println("Moving the car into truck" + b.canMoveNumSpaces(new Space(2, 0), 2));		
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(3, 3), -2));
		System.out.println("Moving lower auto up " + b.canMoveNumSpaces(new Space(4, 3), -2));
		System.out.println("Moving upper auto up " + b.canMoveNumSpaces(new Space(0, 3), -1));
		System.out.println("Moving upper auto up " + b.canMoveNumSpaces(new Space(1, 3), -1));
	}
}
