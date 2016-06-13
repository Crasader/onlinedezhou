package com.oo58.game.texaspoker;

import com.unionpay.UPPayAssistEx;
import com.unionpay.uppay.PayActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class UniPaying extends Activity {
	private String order_id = "";
	private String money = "";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		Log.i("lvjian", "dd=====dddddddddddddddddddddddddddddd=");
		Intent intent = getIntent();
		order_id = intent.getStringExtra("order_id");
        Log.i("lvjian", "dddddddd----===>"+order_id);
		money = intent.getExtras().getString("money");
		 Log.i("lvjian", "dddddddd----money===>"+money);
		String spId = null;
		String sysProvider = null;
		UPPayAssistEx.startPayByJAR(UniPaying.this, PayActivity.class, spId,
				sysProvider, order_id, "00");
	}

	// ����������������
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if (data == null) {
			return;
		}
		String str = data.getExtras().getString("pay_result");
		Log.i("lvjian", "str----------------------------------->" + str);
		if (str.equalsIgnoreCase("success")) {
			setMobilePayResult(1);
			finish();
			Log.i("lvjian", "-------------֧���ɹ�------------");
		} else if (str.equalsIgnoreCase("fail")) {
			setMobilePayResult(2);
			finish();
			Log.i("lvjian", "-------------֧��ʧ��------------");
		} else if (str.equalsIgnoreCase("cancel")) {
			setMobilePayResult(3);
			finish();
			Log.i("lvjian", "-------------����ȡ���˱��ζ�����֧��------------");
		}
	}

	public static native void setMobilePayResult(int a);
}
