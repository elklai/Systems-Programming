package bgu.spl.a2;

import junit.framework.TestCase;
import static org.junit.Assert.*;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.Test;


public class PromiseTest extends TestCase {
	

		Promise<Integer> p;
		callback callback;

	@Before
	public void setUp() throws Exception
	{
		this.callback = new callback4Test();
		this.p=new Promise <Integer>();
	}
	
	@After
	public void tearDown() throws Exception
	{
	}
	
	@Test
	public void testGet(){
		try//check if get throw illigalStateException on !isResolved promise
		{
			p.get();
			fail();
		}
		catch(IllegalStateException ex)
		{
			p.resolve(1);
			try//check if get return the right value
			{
				Integer x=1;
				assertEquals(p.get(),x);
			}
			catch(Exception ex2)
			{
				fail();
			}
		}
		
	}
	
	@Test
	public void testIsResolved()
	{
		try//check if right when !isResolved(constructor)
		{
			assertEquals(p.isResolved(),false);
		}
		catch(Exception ex)
		{
			fail();
		}
		try//check if right when isResloved
		{
			p.resolve(2);
			assertEquals(p.isResolved(),true);
		}
		catch(Exception ex)
		{
			fail();
		}

	}
	
	@Test
	public void testResolve()
	{
		try
		{
			p.subscribe(callback);
			p.resolve(3);
			try//check if throw illigalStateException when resolved twice
			{
				p.resolve(7);
				fail();
			}
			catch (IllegalStateException ex)
			{
				Integer x=3;
				assertEquals(p.get(),x);
			}
			catch(Exception ex)
			{ 
				fail();
			}
 		}
		catch (Exception ex)
		{
			fail();
		}
		try//check if all the callbacks complete (subscribers list is empty)
		{
			assertEquals(((callback4Test)callback).getIsEntered(),true );
		}
		catch(Exception ex)
		{
			fail();
		}
	}
	
	@Test
	public void testSubscribe()
	{
		try
		{
		p.resolve(4);
		p.subscribe(callback);
		assertEquals(((callback4Test)callback).getIsEntered(),true );
		}
		catch(Exception ex)
		{
			fail();
		}

	}
	

	public class callback4Test implements callback
	{
		private boolean isEntered;
	
		public callback4Test()
		{
			isEntered=false;
		}
		public void call(){
			isEntered=true;
		}
		public boolean getIsEntered()
		{
			return isEntered;
		}
	}
}