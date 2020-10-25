
public class Date {
    public static boolean isValidDate(int month, int day, int year) {
    	 if(month <= 0 || month > 12) {
   		  return false;
   		 }
	   	 if(day < 0 && day >= 31) {
	   	   if(month == 2 && day > 28) {
	   		   return false;
	   	   }
	   	   if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
	   		   return false;   
	   	   }
	   	 }
       return true;
    }
}
