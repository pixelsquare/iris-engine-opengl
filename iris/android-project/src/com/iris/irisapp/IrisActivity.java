package com.iris.irisapp;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

//import com.iris.irisapp.R;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

public class IrisActivity extends Activity implements GLSurfaceView.Renderer
{
	// Log tag for iris activity
	private static final String LOG_TAG = "IrisActivity";	
	
	// ES2
	private GLSurfaceView m_glSurfaceView;
	private boolean m_isSurfaceViewInitialized;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
		Log.d(LOG_TAG, "onCreate");
		
		// Get Current Activity
		final ActivityManager activityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
		
		// Get Activity Configuration
		final ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
		
		// Does our device support es2?
		final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;
		
		if(supportsEs2)
		{
			// Initialize Surface View
			m_glSurfaceView = new GLSurfaceView(this);
			
			// Force GL context client version to 2
			m_glSurfaceView.setEGLContextClientVersion(2);
			
			// Set our custom renderer class
			m_glSurfaceView.setRenderer(this);
			
			// Set local variable
			m_isSurfaceViewInitialized = true;
			
			// Set content view to gl surface view
			setContentView(m_glSurfaceView);
		}
		else
		{
			// show a toast that informs the user about device's opengl version
			Toast.makeText(this, "This device does not support OpenGL ES 2.0", Toast.LENGTH_LONG).show();
			return;
		}
    }

	@Override
	public void onStart()
	{
		super.onStart();
		Log.d(LOG_TAG, "onStart");
	}
	
	@Override
	public void onResume()
	{
		super.onResume();
		Log.d(LOG_TAG, "onResume");
		
		if(m_isSurfaceViewInitialized)
		{
			m_glSurfaceView.onResume();
		}
	}
	
	@Override
	public void onPause()
	{
		super.onPause();
		Log.d(LOG_TAG, "onPause");
		
		if(m_isSurfaceViewInitialized)
		{
			m_glSurfaceView.onPause();
		}
	}
	
	@Override
	public void onStop()
	{
		super.onStop();
		Log.d(LOG_TAG, "onStop");
	}
	
	@Override
	public void onDestroy()
	{
		super.onDestroy();
		Log.d(LOG_TAG, "onDestroy");
	}
	
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        //getMenuInflater().inflate(R.menu.iris, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) 
    {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
       // if (id == R.id.action_settings) 
       // {
        //    return true;
        //}
        return super.onOptionsItemSelected(item);
    }    

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) 
	{
		Log.d(LOG_TAG, "onSurfaceCreated");	
		
		AssetManager assetManager = getAssets();
		String assetAbsolutePath = getFilesDir().getAbsolutePath();		
		JNIBridge.SetAssetManager(assetManager, assetAbsolutePath);

		JNIBridge.InitializeGL();
		JNIBridge.Awake();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) 
	{
		Log.d(LOG_TAG, "onSurfaceChanged");
		JNIBridge.OnWindowChanged(width, height);
	}
	
	@Override
	public void onDrawFrame(GL10 gl) 
	{
		JNIBridge.Start();
		
		JNIBridge.FixedUpdate();
		JNIBridge.Update();		
		
		JNIBridge.OnPreRender();
		JNIBridge.OnRender();
		JNIBridge.OnPostRender();
		
		JNIBridge.LateUpdate();				
	}
}
