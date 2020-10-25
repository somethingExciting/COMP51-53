import java.util.Timer;

public class primes {
	
	public primes() {
		
	}
	
	public int euclid(int m, int n) {
		int gcd = 0;
		
		if(n == 0) {
			return m;
		}
		else {
			while (n != 0) {
				gcd = m % n;
			}
			return gcd;
		}
	}
	
	public int consecutive(int m, int n) {
		int t = java.lang.Math.min(m, n);
		
		while(t > 0) {
			if(m%t == 0) {
				if(n%t == 0) {
					return t;
				}
				t--;
			}
			t--;
		}
	}
	
	public int middleSchool(int m, int n) {
		Vector<int> numListM = new Vector<int>;
		Vector<int> numListN = new Vector<int>;
		Vector<int> primesM = new  Vector<int>;
		Vector<int> primesN = new Vector<int>;
		Vector<int> common = new Vector<int>;
		int amount = 0;
		
		for(int i = 0; i < m; i++) {
			numListM.addElement(i);
		}
		
		for(int i = 0; i < n; i++) {
			numListN.addElement(i);
		}
		
		for(int i = 2; i < numListM.length(); i++) {
			for(int j = 2; j < numListM.length(); i++) {
				if(numListM[i] % i == 0) {
					numListM[i] = 0;
				}
			}
		}
		
		for (int i = 2; i < numListM.size(); i++) {
			if (numListM[i] != 0) {
				primesM.addElement(i);
			}
		}
		
		for (int i = 2; i < numListN.size(); i++) {
			for (int j = 2; j < numListN.size(); j++) {
				if (numListN[i] % i == 0) {
					numListN[i] = 0;
				}
			}
		}
		
		for (int i = 2; i < numListN.size(); i++) {
			if (numListN[i] != 0) {
				primesN.addElement(i);
			}
		}
		
		for(int i = 0; i < primesM.size(); i++) {
			for(int j = 0; j < primesN.size(); j++) {
				if(primesM [i] == primesN[j]) {
					common.addElement(i);
				}
			}
		}
		
		for(int i = 0; i < common.size(); i++) {
			amount += common[i];
		}
		return amount;		
	}
	
	public static void main(String[] args) {
		primes prime = new primes();
		double start = System.nanoTime();
		prime.euclid(3, 6);
		double finish = System.nanoTime();
		System.out.print("Time elapsed for euclid: " + (finish - start));
		
		start = System.nanoTime();
		prime.consecutive(9, 18);
		finish = System.nanoTime();
		System.out.print("Time elapsed for consecutive integer checking: " + (finish - start));
		
		start = System.nanoTime();
		prime.middleSchool(2, 16);
		finish = System.nanoTime();
		System.out.print("Time elapsed for middle school: " + (finish - start));
	}

}
