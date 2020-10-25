import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;

public class ACMLab extends GraphicsProgram {
	public static final int PROGRAM_HEIGHT = 600;
	public static final int PROGRAM_WIDTH = 800;

	public void init() {
		setSize(PROGRAM_WIDTH, PROGRAM_HEIGHT);
		requestFocus();
	}
	
	public void run() {
		GLabel label = new GLabel("Hello World", 300, 300);
		label.setColor(Color.red);
		label.setFont("Arial-Bold-24");
		add(label);
		GRect rect = new GRect(125, 250, 200, 100);
		rect.setFillColor(Color.cyan);
		rect.setFilled(true);
		add(rect);
		GRect rect2 = new GRect(435, 250, 200, 100);
		rect2.setFillColor(Color.cyan);
		rect2.setFilled(true);
		add(rect2);
		GOval oval = new GOval(225, 225, 300, 300);
		oval.setFillColor(Color.green);
		oval.setFilled(true);
		add(oval);
		GOval oval2 = new GOval(225, 500, 300, 100);
		oval2.setFillColor(Color.yellow);
		oval2.setFilled(true);
		add(oval2);
		GLine line = new GLine(100, 200, 300, 200);
		line.setColor(Color.orange);
		add(line);
		GImage image = new GImage("robot.png", 250, 100);
		add(image);
		for(int i = 0; i < 25; i++) {
			oval2.move(-3, 2);
			pause(1);
		}
	}
}
