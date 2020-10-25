import static org.junit.Assert.*;

import org.junit.Test;

public class DateTest {

	@Test
	public void testIsValidDateBasic() {
		assertTrue(Date.isValidDate(5, 20, 2017));
		assertFalse(Date.isValidDate(46, 4, 2017));
		assertTrue(Date.isValidDate(3, 1, 2017));
	}
	
	@Test
	public void testDatesAdvanced() {
		assertTrue(Date.isValidDate(4, 15, 2017));
		assertFalse(Date.isValidDate(11, 31, 2017));
		assertFalse(Date.isValidDate(1, 41, 2017));
	}
	
	@Test
	public void testDatesEdge() {
		assertFalse(Date.isValidDate(0, 0, 2017));
		assertFalse(Date.isValidDate(-3, 2, 2017));
		assertTrue(Date.isValidDate(1, 1, 2017));
	}
	
}
/*
1. I made 3 different test methods in order to test 3 different input cases: basic, advanced, and edge
2. Basic: tests dates that are either correct(ex. 4/15/2017) or radically incorrect(ex. 14/90/2017)
   Advanced: tests dates that could potentially be real dates(ex. 11/31/2017)
   Edge: tests dates that have incorrect inputs, such as negative numbers, characters, or 0
3. assertFalse(Date.isValidDate(46, 4, 2017));
   assertTrue(Date.isValidDate(3, 1, 2017));
   assertTrue(Date.isValidDate(4, 15, 2017));
   assertFalse(Date.isValidDate(11, 31, 2017));
   assertFalse(Date.isValidDate(0, 0, 2017));
*/

