package com.oo58.game.texaspoker;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.ContentValues;
import android.content.Intent;
import android.graphics.Bitmap;
import android.hardware.Camera;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.util.Log;
import android.view.Surface;

public class PhotoManagerActivity extends Activity{

	private static final String IMAGE_UNSPECIFIED = "image/*";
	private static final int ALBUM_REQUEST_CODE = 111;
	private static final int CAMERA_REQUEST_CODE = 112;
	private static final int CROP_REQUEST_CODE = 114;

	
	public static final int RESULT_EXIT_PHOTO = 15 ;
	private static final String TAG = "PhotoManagerActivity";
	private Uri photoUri;
//	AppActivity act;
	private ProgressDialog m_pDialog; 
	
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		Intent intent = getIntent() ;
		String sFun = intent.getStringExtra("fun") ;
		if(sFun.equals("takephoto")){
			showTakePhoto();
		}
		if(sFun.equals("photoalbum")){
			showPhotoAlbum()  ;
		}
		
		initDialog() ;
	}

	private void initDialog(){
		//����ProgressDialog����
        m_pDialog = new ProgressDialog(this);

// ���ý�������񣬷��ΪԲ�Σ���ת��
        m_pDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        
        // ����ProgressDialog ��ʾ��Ϣ
        m_pDialog.setMessage("���Եȡ�����");
        
        // ����ProgressDialog �Ľ������Ƿ���ȷ
        m_pDialog.setIndeterminate(false);
           
        // ����ProgressDialog �Ƿ���԰��˻ذ���ȡ��
        m_pDialog.setCancelable(false);
       
        m_pDialog.dismiss() ;
	}
	
//	public PhotoManagerActivity(AppActivity act) {
//		this.act = act;
//		
//
//	}

	// ����һ���Ե�ǰʱ��Ϊ���Ƶ��ļ�
//	File tempFile = new File(Environment.getExternalStorageDirectory(),
//			getPhotoFileName());

	// ʹ��ϵͳ��ǰ���ڼ��Ե�����Ϊ��Ƭ������
	private String getPhotoFileName() {
		Date date = new Date(System.currentTimeMillis());
		SimpleDateFormat dateFormat = new SimpleDateFormat(
				"'IMG'_yyyyMMdd_HHmmss");
		return dateFormat.format(date) + ".jpg";
	}
	public static void setCameraDisplayOrientation (Activity activity, int cameraId, android.hardware.Camera camera) {  
	    android.hardware.Camera.CameraInfo info = new android.hardware.Camera.CameraInfo();  
	    android.hardware.Camera.getCameraInfo (cameraId , info);  
	    int rotation = activity.getWindowManager ().getDefaultDisplay ().getRotation ();  
	    int degrees = 0;  
	    switch (rotation) {  
	        case Surface.ROTATION_0:  
	            degrees = 0;  
	            break;  
	        case Surface.ROTATION_90:  
	            degrees = 90;  
	            break;  
	        case Surface.ROTATION_180:  
	            degrees = 180;  
	            break;  
	        case Surface.ROTATION_270:  
	            degrees = 270;  
	            break;  
	    }  
	    int result;  
	    if (info.facing == Camera.CameraInfo.CAMERA_FACING_FRONT) {  
	        result = (info.orientation + degrees) % 360;  
	        result = (360 - result) % 360;   // compensate the mirror  
	    } else {  
	        // back-facing  
	        result = ( info.orientation - degrees + 360) % 360;  
	    }  
	    camera.setDisplayOrientation (result);  
	}
	

	public void showTakePhoto() {

		Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
		ContentValues values = new ContentValues();
		photoUri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);	
		intent.putExtra(MediaStore.EXTRA_OUTPUT, photoUri);
		startActivityForResult(intent, CAMERA_REQUEST_CODE);

	}

	public void showPhotoAlbum() {

		Intent intent = new Intent(Intent.ACTION_PICK, null);
		intent.setDataAndType(MediaStore.Images.Media.EXTERNAL_CONTENT_URI,IMAGE_UNSPECIFIED);
		startActivityForResult(intent, ALBUM_REQUEST_CODE);
	}

	/**
	 * ��ʼ�ü�
	 * 
	 * @param uri
	 */
	private void startCrop(Uri uri) {
		
	
		
		
		Intent intent = new Intent("com.android.camera.action.CROP");// ����Androidϵͳ�Դ���һ��ͼƬ����ҳ��,
		intent.setDataAndType(uri, IMAGE_UNSPECIFIED);
		intent.putExtra("crop", "true");// �����޼�
		// aspectX aspectY �ǿ�ߵı���
		intent.putExtra("aspectX", 1);
		intent.putExtra("aspectY", 1);
		// outputX outputY �ǲü�ͼƬ���
		intent.putExtra("outputX", 200);
		intent.putExtra("outputY", 200);
		intent.putExtra("scale", true);
		intent.putExtra("return-data", true);
		intent.putExtra("noFaceDetection", true);
		intent.putExtra("scaleUpIfNeeded", true);//�ڱ�
		intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());
		startActivityForResult(intent, CROP_REQUEST_CODE);
		
	}

	/**
	 * �ж�sdcard���Ƿ����
	 * 
	 * @return �������� true ���� false ������
	 */
	private boolean isSDCardCanUser() {
		return Environment.getExternalStorageState().equals(
				Environment.MEDIA_MOUNTED);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data) ;
		if(resultCode == -1){
		
			switch (requestCode) {
			case ALBUM_REQUEST_CODE:
			{
				Log.i(TAG, "��ᣬ��ʼ�ü�");
				Log.i(TAG, "��� [ " + data + " ]");
		
				Uri localUri = null;
				if ((data != null) && (data.getData() != null)) {
					localUri = data.getData();
				}
				// һЩ�����޷���getData�л�ȡuri�������ֶ�ָ�����պ�洢��Ƭ��Uri
				if (localUri == null) {
					if (photoUri != null) {
						localUri = photoUri;
					}
				}
				if(localUri!=null){
					startCrop(localUri);
				}
					
			}

				break;
			case CAMERA_REQUEST_CODE:
			{
				
				Uri localUri = null;
				if ((data != null) && (data.getData() != null)) {
					localUri = data.getData();
				}
				// һЩ�����޷���getData�л�ȡuri�������ֶ�ָ�����պ�洢��Ƭ��Uri
				if (localUri == null) {
					if (photoUri != null) {
						localUri = photoUri;
					}
				}
				startCrop(localUri);
				
			}

				break;
			case CROP_REQUEST_CODE:
			{
				m_pDialog.show() ;
				Log.i(TAG, "���ü��ɹ�");
				Log.i(TAG, "�ü��Ժ� [ " + data + " ]");
				if (data == null) {
					// TODO ���֮ǰ�Ժ������ù���ʾ֮ǰ���õ�ͼƬ ������ʾĬ�ϵ�ͼƬ
					m_pDialog.dismiss() ;
					return;
				}
				
				Uri localUri = null;
				if ((data != null) && (data.getData() != null)) {
					localUri = data.getData();
				}
				// һЩ�����޷���getData�л�ȡuri�������ֶ�ָ�����պ�洢��Ƭ��Uri
				if (localUri == null) {
					if (photoUri != null) {
						localUri = photoUri;
					}
				}
				
				Bundle extras = data.getExtras();
				
				if (extras != null) {
					m_pDialog.show() ;
					Bitmap photo = extras.getParcelable("data");
				
					final ByteArrayOutputStream stream = new ByteArrayOutputStream();
					photo.compress(Bitmap.CompressFormat.JPEG, 100, stream);// (0-100)ѹ���ļ�
					final String path = Cocos2dxHelper.getCocos2dxWritablePath()+ "/header.jpg" ;
									
					
					saveMyBitmap(path, photo);//�ȱ����ȡ�ĵ�����
					callUploaderPhoto() ;//�ϴ���������
					callExit() ;
//					new Thread(){
//						@Override
//						public void run() {				
////							uploadFile200(  stream.toByteArray());
//							uploadFile200(path) ;
//						};
//					}.start() ;

					
				}
				m_pDialog.dismiss() ;
			}
			
				break;
			default:
				break;
			}
			
			
		}else{
			
			callExit() ;
		}
		
		

	}

	private void saveMyBitmap(String bitName, Bitmap mBitmap) {
		File file = new File(bitName);
//		File file = new File("/sdcard/" + bitName + ".jpg");
		FileOutputStream fOut = null;
		try {

			file.createNewFile();
			fOut = new FileOutputStream(file);
			mBitmap.compress(Bitmap.CompressFormat.JPEG, 100, fOut);
			fOut.flush();
			fOut.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

	public void callExit() {
		 Intent intent = new Intent();
		 setResult(RESULT_EXIT_PHOTO, intent);
		 this.finish() ;
	}
	
	/* �ϴ��ļ���Server�ķ��� */
	private void uploadFile200(String uploadFile) {
		String openid = AppActivity.mOpenID;
		String openkey = AppActivity.mOpenKey;
		String timestamp = System.currentTimeMillis()/1000+"";
		String sUrl = "http://picture.0058.com/texas_useravator.php?type=200&openid="
				+ openid + "&openkey=" + openkey + "&timestamp=" + timestamp;
		try {
			URL url = new URL(sUrl);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();
			con.setDoInput(true);
			con.setDoOutput(true);
			con.setUseCaches(false);
			con.setRequestMethod("POST");
			/* ����DataOutputStream */
			DataOutputStream ds = new DataOutputStream(con.getOutputStream());
			FileInputStream fStream = new FileInputStream(uploadFile);
			/* ����ÿ��д��1024bytes */
			int bufferSize = 1024;
			byte[] buffer = new byte[bufferSize];
			int length = -1;
			/* ���ļ���ȡ������������ */
			while ((length = fStream.read(buffer)) != -1) {
				/* ������д��DataOutputStream�� */
				ds.write(buffer, 0, length);
			}
			/* close streams */
			fStream.close();
			ds.flush();
			/* ȡ��Response���� */
			int res = con.getResponseCode();
			if (res == 200) {
				InputStream is = con.getInputStream();
				int ch;
				StringBuffer b = new StringBuffer();
				while ((ch = is.read()) != -1) {
					b.append((char) ch);
				}
				Log.i("log", "���ؽ��--------200-----------��" + b.toString());
				
			} else {
			}
			m_pDialog.dismiss() ;
			ds.close();
		} catch (Exception e) {
		}
	}
	
	
	
	private void uploadFile200(byte[] buffer) {
		String openid = AppActivity.mOpenID;
		String openkey = AppActivity.mOpenKey;
		String timestamp = System.currentTimeMillis()/1000+"";
		String sUrl = "http://picture.0058.com/texas_useravator.php?type=200&openid="
				+ openid + "&openkey=" + openkey + "&timestamp=" + timestamp;
		try {
			URL url = new URL(sUrl);
			HttpURLConnection con = (HttpURLConnection) url.openConnection();
			con.setDoInput(true);
			con.setDoOutput(true);
			con.setUseCaches(false);
			con.setRequestMethod("POST");

			/* ����DataOutputStream */
			DataOutputStream ds = new DataOutputStream(con.getOutputStream());
			//д�����ļ�
			ds.write(buffer);
			//����
			ds.flush();
			/* ȡ��Response���� */
			int res = con.getResponseCode();
			if (res == 200) {
				InputStream is = con.getInputStream();
				int ch;
				StringBuffer b = new StringBuffer();
				while ((ch = is.read()) != -1) {
					b.append((char) ch);
				}
				Log.i("log", "���ؽ��--------200-----------��" + b.toString());

			} else {
			}
			ds.close();
		} catch (Exception e) {
		}
	}
	
	public static native void callUploaderPhoto();

}
