import acm.graphics.*;
import acm.program.*;
import acm.util.*;
import java.awt.*;
import java.awt.event.*;

public class Ball extends GraphicsProgram {
	public static final int WINDOW_WIDTH = 800;
	public static final int WINDOW_HEIGHT = 600;
	public static final int BALL_SIZE = 100;
	public static final int BREAK_MS = 30;
	public static final int INIT_X_VELOCITY = 5;
	
	private GOval ball;
	private int xVelocity;
	private RandomGenerator rgen;
	
	public void run() {
		rgen = RandomGenerator.getInstance();
		xVelocity = INIT_X_VELOCITY;
		
		ball = new GOval(WINDOW_HEIGHT/2-BALL_SIZE/2, WINDOW_WIDTH/2-BALL_SIZE/2, BALL_SIZE, BALL_SIZE);
		ball.setColor(Color.RED);
		ball.setFilled(true);
		add(ball);
		
		addMouseListeners();
		animateBall();
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		if(getElementAt(e.getX(), e.getY()) == ball) {
			ball.setColor(rgen.nextColor());
		}
		ball.setLocation(ball.getX(), e.getY());
		System.out.println("Mouse is being pressed!");
	}
	
	@Override 
	public void mouseReleased(MouseEvent e) {
		System.out.println("Mouse has been released");
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		System.out.println("CLICK");
	}
	
	@Override
	public void mouseEntered(MouseEvent e) {
		System.out.println("Mouse has entered the window space");
	}
	
	@Override
	public void mouseExited(MouseEvent e) {
		System.out.println("Mouse has exited the window space");
	}
	
	@Override
	public void mouseMoved(MouseEvent e) {
		System.out.println("Mouse is moving");
	}
	
	@Override
	public void mouseDragged(MouseEvent e) {
		System.out.println("Mouse is getting DRAGGED");
	}
	
	private void animateBall() {
		while(true) {
			ball.move(xVelocity, 0);
			if(outOfBounds()) {
				xVelocity *= -1;
			}
			pause(BREAK_MS);
		}
	}
	
	private boolean outOfBounds() {
		double x = ball.getX();
		return (x < 0 && xVelocity < 0 || x > WINDOW_WIDTH && xVelocity > 0);
	}

	public void init() {
		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		requestFocus();
	}
}