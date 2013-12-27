package com.example.ardumotica;

import android.os.*;
import java.io.IOException;
//import java.util.ArrayList;
//import java.util.List;

//import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
//import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
//import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import com.example.ardumotica.R;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
//import android.view.Menu;
import android.view.View;
import android.widget.Button;

@TargetApi(Build.VERSION_CODES.GINGERBREAD)
@SuppressLint("NewApi")
public class MainActivity extends Activity {
    /** Called when the activity is first created. */
	Button sendButton;
	Button sendButtonO;

	
	@SuppressLint("NewApi")
	@TargetApi(Build.VERSION_CODES.GINGERBREAD)
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        if (android.os.Build.VERSION.SDK_INT > 9) {
            StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
            StrictMode.setThreadPolicy(policy);
        }
        
        sendButton = (Button) findViewById(R.id.sendButton);
       
        sendButtonO = (Button) findViewById(R.id.sendButtonOff);
                 
	}
	
	public void send(View v){
		  HttpParams params = new BasicHttpParams();
		  HttpConnectionParams.setConnectionTimeout(params, 200);
		  HttpConnectionParams.setSoTimeout(params, 200);	
		  HttpClient httpclient = new DefaultHttpClient(params);
	 
		 
	          // put the address to your server and receiver file here
		  HttpPost httppost = new HttpPost("http://192.168.1.50/?dig=1");
	          try {
	    
		   	   httpclient.execute(httppost); // send the parameter to the server
		      } catch (ClientProtocolException e) {
		   
		      } catch (IOException e) {

		     }
	    }
	
	public void sendOff(View v){
		  HttpParams params = new BasicHttpParams();
		  HttpConnectionParams.setConnectionTimeout(params, 200);
		  HttpConnectionParams.setSoTimeout(params, 200);	
		  HttpClient httpclient = new DefaultHttpClient(params);

		  HttpPost httppost = new HttpPost("http://192.168.1.50/?dig=0");
		  
	        try {

		   	   httpclient.execute(httppost); // send the parameter to the server
		     } catch (ClientProtocolException e) {
		    	
		     } catch (IOException e) {
		         // TODO Auto-generated catch block
		     } 
	    }
	

}

