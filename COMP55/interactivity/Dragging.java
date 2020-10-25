import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;
import java.awt.event.*;

public class Dragging extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	public static final int SHAPE_SIZE = 100;
	
	private GObject toDrag;
	private int lastX, lastY;
	
	public void run() {
		GOval oval = new GOval(100, 100, SHAPE_SIZE, SHAPE_SIZE);
		oval.setColor(Color.blue);
		oval.setFilled(true);
		add(oval);
		
		GRect rect = new GRect(500, 500, SHAPE_SIZE, SHAPE_SIZE);
		rect.setColor(Color.green);
		rect.setFilled(true);
		add(rect);
		
		addMouseListeners();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		toDrag = getElementAt(e.getX(), e.getY());
		lastX = e.getX();
		lastY = e.getY();		
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		//compare the current coordinates to the last known coordinates
		//do not call setLocation, use the calculations to figure out how much to move the object
		//update the old mouseDragged coordinates with the current coordinates 
		if(toDrag != null ) {
			int distance1 = e.getX() - lastX; 
			int distance2 = e.getY() - lastY;
			toDrag.move(distance1, distance2);
			lastX = e.getX();
			lastY = e.getY();
			//toDrag.setLocation(e.getX() - SHAPE_SIZE/2, e.getY() - SHAPE_SIZE/2);
		}
	}
	
	@Override
	public void mouseReleased(MouseEvent e) {
		toDrag = null;
	}
	
	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		requestFocus();
	}
}
