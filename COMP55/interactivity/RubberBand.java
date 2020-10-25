import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;
import java.awt.event.*;

public class RubberBand extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	private GLine newLine;
	
	public void run() {
		addMouseListeners();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		newLine = new GLine(e.getX(), e.getY(), e.getX(), e.getY());
		add(newLine);
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		newLine.setEndPoint(e.getX(), e.getY());
	}
	
	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		requestFocus();
	}
}
