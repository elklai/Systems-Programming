package bgu.spl.a2;

import junit.framework.TestCase;
import static org.junit.Assert.*;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;


public class VersionMonitorTest extends TestCase {
	
	private VersionMonitor moni;
	
	
	
	@Before    // i dont know what this is
	public void setUp() throws Exception {
		this.moni = new VersionMonitor();
	}
	
	@After	// i dont know what this is
	public void tearDown() throws Exception {
	}

	@Test
	public void testGetVersion()
	{
		assertTrue( 0 == this.moni.getVersion());
	}
	

	@Test
	public void testInc()
	{
		int x = moni.getVersion();
		Inc(moni); // increase by 5
		assertTrue( x + 5 == this.moni.getVersion());
	}
	

	@Test
	public void testAwait()
	{
		RunningAndAwaiting helloPrinter = new RunningAndAwaiting( this.moni );// runnable
		
		Thread helloThread = new Thread(helloPrinter);
		
		helloThread.start(); 
		
		assertFalse(helloThread.isAlive());// should be waiting because version is still 0
		this.moni.inc();
		notifyAll();  //im not sure if i need to right this line
		assertTrue(helloThread.isAlive());//should be running because version is now 1
		
	}
	
	public static void Inc( VersionMonitor moni)
	{
		for( int i = 0 ; i < 5 ; i++) 
			moni.inc();
	}


	class RunningAndAwaiting implements Runnable {
		
		private VersionMonitor moni;
		
		RunningAndAwaiting( VersionMonitor moni ) {
			this.moni = moni;
		}
	 
		public void run() {
			try {
				int x = moni.getVersion();
				moni.await( x ); // wait untill version increased
			} catch (InterruptedException e) {
				Assert.fail();
			}
		}
	}

}

