

# Solution

Sample code, incomplete.

```java
import java.util.LinkedList;
import java.util.Random;
import java.util.concurrent.ConcurrentLinkedQueue;

abstract class Fruit {
	protected String m_type;
	public Fruit() {
		m_type = "Fruit";
	}
	public String GetType() {return m_type;}
	protected abstract void SetType();
}

class Banana extends Fruit {
	public Banana(){}
	@Override 
	protected void SetType() {
		m_type = "Banana";
	}
}

class Apple extends Fruit {
	public Apple(){}
	@Override 
	protected void SetType() {
		m_type = "Apple";
	}
}

class Pear extends Fruit {
	public Pear(){}
	@Override 
	protected void SetType() {
		m_type = "Pear";
	}
}



class Refridge {
	public Refridge() {
		m_bananas = new ConcurrentLinkedQueue<Banana>();
		m_apples = new ConcurrentLinkedQueue<Apple>();
		m_pears = new ConcurrentLinkedQueue<Pear>();
	}
	
	public void AddFruit(String producer_name, String type) {
		if (type == "BANANA") m_bananas.add(new Banana());
		if (type == "APPLE") m_apples.add(new Apple());
		if (type == "PEAR")  m_pears.add(new Pear());
		System.out.println(producer_name +" added  " + type);
	}
	
	public Fruit TakeFruit(String consumer_name, String type) {
		Fruit reval = null;
		if (type == "BANANA") reval =  m_bananas.poll();
		if (type == "APPLE") reval =  m_apples.poll();
		if (type == "PEAR") reval =  m_pears.poll();
		if (reval != null) System.out.println(consumer_name + " took  " + type);
		return reval;
	}
	
	private ConcurrentLinkedQueue<Banana> m_bananas;
	private ConcurrentLinkedQueue<Apple> m_apples;
	private ConcurrentLinkedQueue<Pear> m_pears;
}


class Producer extends Thread {
	private String m_name;
	private Refridge m_refridge;
	public Producer(String name, Refridge refridge) {
		m_name = name;
		m_refridge = refridge;
	}

	@Override
	public void run() {
		String[] types = {"APPLE", "BANANA", "PEAR"};
		Random rand = new Random(); 
		for (int i = 0;i < 3; ++i) {
			m_refridge.AddFruit(m_name, types[rand.nextInt(3)]);
		}
		
	}
} 

class Consumer extends Thread{
	private String m_name;
	private Refridge m_refridge;
	
	public Consumer(String name, Refridge refridge) {
		m_name = name;
		m_refridge = refridge;
	}
	@Override
	public void run() {
		String[] types = {"APPLE", "BANANA", "PEAR"};
		Random rand = new Random(); 
		while (true) {
			m_refridge.TakeFruit(m_name, types[rand.nextInt(3)]);
		}
	}
}

public class TestThread {

   public static void main(String[] args) {
	   Refridge refridge = new Refridge();
	   
	   Consumer consumer_one = new Consumer("Consumer One", refridge);
	   Consumer consumer_two = new Consumer("Consumer Two", refridge);
	   Consumer consumer_three = new Consumer("Consumer Two", refridge);
	   
	   Producer producer_one = new Producer("Prodecuer One", refridge);
	   Producer producer_two = new Producer("Prodecuer Two", refridge);
	   
	   Thread c1 = new Thread(consumer_one);
       Thread c2 = new Thread(consumer_two);
       Thread c3 = new Thread(consumer_three);
       
       Thread p1 = new Thread(producer_one);
       Thread p2 = new Thread(producer_two);
       
       c1.start();
       c2.start();
       c3.start();
       
       p1.start();
       p2.start();
       
       try {
    	   c1.join();
	       c2.join();
	       c3.join();
	       
	       p1.join();
	       p2.join();
       } catch (InterruptedException e) {
    	   // TODO Auto-generated catch block
    	   e.printStackTrace();
       }
       System.out.println("Program complete.");
   }
}


```
