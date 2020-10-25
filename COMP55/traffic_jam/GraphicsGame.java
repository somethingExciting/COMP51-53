import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.util.*;

import acm.graphics.*;
import acm.program.*;

public class GraphicsGame extends GraphicsProgram {
	/**
	 * Here are all of the constants
	 */
	public static final int PROGRAM_WIDTH = 500;
	public static final int PROGRAM_HEIGHT = 500;
	public static final String lABEL_FONT = "Arial-Bold-22";
	public static final String EXIT_SIGN = "EXIT";
	public static final String IMG_FILENAME_PATH = "images/";
	public static final String IMG_EXTENSION = ".png";
	public static final String VERTICAL_IMG_FILENAME = "_vert";

	public static final double EXIT_SCALE_X = 0.1;
	public static final double EXIT_SCALE_Y = 0.4;
	public static final double WINNING_SCALE_X = 0.1;

	// instance variables

	private Space vehicleLoc; //location of the vehicle
	private double lastX; //last known X coordinate
	private double lastY; //last known Y coordinate
	private boolean isVertical; //if the image/object is vertical or not
	private GObject lastCar; // holds the image that the user clicked
	private Level level; //instance level
	private boolean listening; //if the mouselisteners have been implemented
	private boolean clicked; //if the image/object was clicked

	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
		Level level = new Level();
		level.setUpLevel();
	}

	public void run() {
		drawLevel();
	}

	private void drawLevel() {
		drawGridLines();
		drawCars();
		drawWinningTile();
	}

	/**
	 * This should draw the label EXIT and add it to the space that represents the
	 * winning tile.
	 */
	private void drawWinningTile() {
		double coordinates[] = convertRowColumnToXY(level.getExitTile());
		GLabel label = new GLabel(EXIT_SIGN, coordinates[0] + (EXIT_SCALE_X * spaceWidth()),
				coordinates[1] + (EXIT_SCALE_Y * spaceHeight()));
		label.setColor(Color.RED);
		label.setFont(lABEL_FONT);
		label.sendToFront();
		add(label);
	}

	/**
	 * draw the lines of the grid. Test this out and make sure you have it working
	 * first. Should draw the number of grids based on the number of rows and
	 * columns in Level
	 */
	private void drawGridLines() {
		drawRowLines(level.getRows());
		drawColLines(level.getColumns());
	}

	private void drawRowLines(int rows) {
		double pixels = 0;
		for (int i = 0; i < rows - 1; i++) {
			pixels += spaceHeight();
			add(new GLine(0.0, pixels, PROGRAM_WIDTH, pixels));
		}

	}

	private void drawColLines(int cols) {
		double pixels = 0;
		for (int i = 0; i < cols - 1; i++) {
			pixels += spaceWidth();
			add(new GLine(pixels, 0.0, pixels, PROGRAM_HEIGHT));
		}
	}

	/**
	 * Maybe given a list of all the cars, you can go through them and call drawCar
	 * on each?
	 */
	private void drawCars() {
		ArrayList<Vehicle> allVehicles = level.getVehiclesOnBoard();
		for (Vehicle v : allVehicles) {
			drawCar(v);
		}
		listening = true;
	}

	/**
	 * Given a vehicle object, which we will call v, use the information from that
	 * vehicle to then create a GImage and add it to the screen. Make sure to use
	 * the constants for the image path ("/images"), the extension ".png" and the
	 * additional suffix to the filename if the object is vertical when creating
	 * your GImage. Also make sure to set the images size according to the size of
	 * your spaces
	 * 
	 * @param v
	 *            the Vehicle object to be drawn
	 */
	private void drawCar(Vehicle v) {
		String name;
		double[] coordinates = convertRowColumnToXY(v.getStart());
		double[] size = new double[2];

		if (v.isVertical) {
			name = IMG_FILENAME_PATH + v.getVehicleType().toString() + VERTICAL_IMG_FILENAME + IMG_EXTENSION;
		}
		name = IMG_FILENAME_PATH + v.getVehicleType().toString() + IMG_EXTENSION;
		if (v.isVertical) {
			size[0] = spaceWidth();
			size[1] = spaceHeight() * v.spacesOccupied().length;
		} else {
			size[0] = spaceWidth() * v.spacesOccupied().length;
			size[1] = spaceHeight();
		}
		GImage car = new GImage(name, coordinates[0], coordinates[1]);
		car.setSize(size[0], size[1]);
		car.addMouseListener(new MouseListener() {
			@Override
			public void mousePressed(MouseEvent e) {
				if (listening) {
					Vehicle v = getVehicleFromXY(e.getX(), e.getY());
					if (v != null) {
						clicked = true;
						lastX = e.getX();
						lastY = e.getY();
						lastCar = getElementAt(lastX, lastY);
					}
				}
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				if (listening && clicked) {
					if (level.win()) {
						return;
					}
				}
				clicked = false;
				lastCar = null;
			}

			@Override
			public void mouseClicked(MouseEvent e) {

			}

			@Override
			public void mouseEntered(MouseEvent e) {

			}

			@Override
			public void mouseExited(MouseEvent e) {

			}
		});

		car.addMouseMotionListener(new MouseMotionListener() {
			@Override
			public void mouseDragged(MouseEvent e) {
				if (listening && clicked) {
					if (isVertical) {
						if (moveImage(0.0, e.getY() - lastY)) {
							lastY = e.getY();
						}
					} else {
						if (moveImage(e.getX() - lastX, 0.0)) {
							lastX = e.getX();
						}
					}

				}
			}

			@Override
			public void mouseMoved(MouseEvent e) {

			}
		});
	}
	
	/**
	 * Given xy coordinates, the vehicle is moved to the xy coordinate
	 * 
	 * @param x 
	 * 			the x coordinate in pixels
	 * @param y
	 * 			the y coordinate in pixels
	 * @return whether the vehicle was moved or not
	 */
	public boolean moveImage(double x, double y) {
		lastCar.move(x, y);
		return true;
	}
	
	/**
	 * Given a xy coordinates, return the Vehicle that is currently at those x and y
	 * coordinates, returning null if no Vehicle currently sits at those
	 * coordinates.
	 * 
	 * @param x
	 *            the x coordinate in pixels
	 * @param y
	 *            the y coordinate in pixels
	 * @return the Vehicle object that currently sits at that xy location
	 */
	private Vehicle getVehicleFromXY(double x, double y) {
		return level.getVehicleAt(convertXYToRowColumn(x, y));
	}

	/**
	 * This is a useful helper function to help you calculate the number of spaces
	 * that a vehicle moved while dragging so that you can then send that
	 * information over as numSpacesMoved to that particular Vehicle object.
	 * 
	 * @return the number of spaces that were moved
	 */
	private int calculateSpacesMoved() {
		Space newSpace = convertXYToRowColumn(lastX, lastY);
		if (isVertical) {
			return newSpace.getRow() - vehicleLoc.getRow();
		}
		return newSpace.getCol() - vehicleLoc.getCol();
	}

	/**
	 * Another helper function/method meant to return the rowcol given an x and y
	 * coordinate system. Use this to help you write getVehicleFromXY
	 * 
	 * @param x
	 *            x-coordinate (in pixels)
	 * @param y
	 *            y-coordinate (in pixels)
	 * @return the RowCol associated with that x and y
	 */
	private Space convertXYToRowColumn(double x, double y) {
		Space s = new Space((int) (x / spaceWidth()), (int) (y / spaceHeight()));
		return s;
	}
	
	/**
	 * Another helper function/method meant to return the xy coordinates given a space
	 * 
	 * @param s
	 * 			space
	 * @return the xy coordinates associated with that space
	 */
	private double[] convertRowColumnToXY(Space s) {
		double[] coordinates = new double[2];
		coordinates[0] = s.getCol() * spaceWidth();
		coordinates[1] = s.getRow() * spaceHeight();
		return coordinates;
	}

	/**
	 * 
	 * @return the width (in pixels) of a single space in the grid
	 */
	private double spaceWidth() {
		return PROGRAM_WIDTH / level.getRows();
	}

	/**
	 * 
	 * @return the height in pixels of a single space in the grid
	 */
	private double spaceHeight() {
		return PROGRAM_HEIGHT / level.getColumns();
	}
}
