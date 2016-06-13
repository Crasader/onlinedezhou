package com.oo58.game.texaspoker;



import org.json.JSONObject;

import com.tencent.tauth.IUiListener;
import com.tencent.tauth.Tencent;
import com.tencent.tauth.UiError;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

public class LoginActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		// ִ��qq��¼����
		qqlogin();
		
		//this.overridePendingTransition(enterAnim, exitAnim)
		this.overridePendingTransition(R.anim.start_anim, R.anim.end_anim);
	}

	private void qqlogin() {
		Tencent mTencent = Tencent.createInstance("1104823392", this);

		IUiListener listener = new BaseUiListener() {

			@Override
			protected void doComplete(JSONObject paramAnonymousJSONObject) {
				Log.i("lvjian",
						"qq--------->" + paramAnonymousJSONObject.toString());
				String access_token = paramAnonymousJSONObject
						.optString("access_token");

				String openid = paramAnonymousJSONObject.optString("openid");
				Log.i("lvjian", "access_token------------------->"
						+ access_token);
				Log.i("lvjian", "openid--------------->" + openid);
				setQQLoginResult(openid, access_token);
                finish();
				// ��ȡ�ɹ�����access_token,openidȥ��¼�����Լ��ķ������ӿڣ���ȡ�û���Ϣ
			}
		};
				
		mTencent.login(this, "all", listener);
		Log.i("lvjian", "================qq_login===============");
	}
	
	private class BaseUiListener implements IUiListener {

		@Override
		public void onComplete(Object response) {
			// Utils.showToast(getApplicationContext(), response.toString()
			// + "��¼�ɹ�");
			doComplete((JSONObject) response);
		}

		protected void doComplete(JSONObject values) {
			Log.i("lvjian", "doComplete");
			 finish();
		}

		@Override
		public void onError(UiError e) {
			Log.i("lvjian", "onError");
			 finish();
		}

		@Override
		public void onCancel() {
			Log.i("lvjian", "onCancel");
			 finish();
		}
	}
	
	private static native void setQQLoginResult(String openID, String token);
}
