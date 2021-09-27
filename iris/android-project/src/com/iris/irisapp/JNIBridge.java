package com.iris.irisapp;

import android.content.res.AssetManager;

public class JNIBridge 
{
	static
	{
		System.loadLibrary("Iris");
		System.loadLibrary("Main");
	}
	
	public static native void InitializeGL();
	
	public static native void OnWindowChanged(int p_width, int p_height);
	
	public static native void Awake();
	
	public static native void Start();
	
	
	public static native void FixedUpdate();
	
	public static native void Update();
	
	public static native void LateUpdate();
	
	
	public static native void OnPreRender();
	
	public static native void OnRender();
	
	public static native void OnPostRender();
	
	
	public static native void Shutdown();
	
	public static native void SetAssetManager(AssetManager p_assetManager, String p_internalDir);
}
