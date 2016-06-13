package com.oo58.game.texaspoker;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Random;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.app.FragmentActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import com.alipay.sdk.app.PayTask;
import com.oo58.game.texaspoker.alipay.Keys;
import com.oo58.game.texaspoker.alipay.PayResult;
import com.oo58.game.texaspoker.alipay.Rsa;
import com.oo58.game.texaspoker.alipay.SignUtils;

public class AliPaying extends Activity {
	private String order_id = "";
	private String money = "";
	private String name = "";
	
	private Context mContext = null;

	private static final int SDK_PAY_FLAG = 1;

	private static final int SDK_CHECK_FLAG = 2;
	
	private Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
			switch (msg.what) {
			case SDK_PAY_FLAG: {
				PayResult payResult = new PayResult((String) msg.obj);
				
				// ֧�������ش˴�֧���������ǩ�������֧����ǩ����Ϣ��ǩԼʱ֧�����ṩ�Ĺ�Կ����ǩ
				String resultInfo = payResult.getResult();
				
				String resultStatus = payResult.getResultStatus();

				// �ж�resultStatus Ϊ��9000�������֧���ɹ�������״̬�������ɲο��ӿ��ĵ�
				if (TextUtils.equals(resultStatus, "9000")) {
					//Toast.makeText(mContext, "֧���ɹ�",
					//		Toast.LENGTH_SHORT).show();
					AliPaying.this.finish();
					UniPaying.setMobilePayResult(1);
				} else {
					// �ж�resultStatus Ϊ�ǡ�9000����������֧��ʧ��
					// ��8000������֧�������Ϊ֧������ԭ�����ϵͳԭ���ڵȴ�֧�����ȷ�ϣ����ս����Ƿ�ɹ��Է�����첽֪ͨΪ׼��С����״̬��
					if (TextUtils.equals(resultStatus, "8000")) {
						//Toast.makeText(mContext, "֧�����ȷ����",
						//		Toast.LENGTH_SHORT).show();
						AliPaying.this.finish();
						UniPaying.setMobilePayResult(3);
					} else {
						// ����ֵ�Ϳ����ж�Ϊ֧��ʧ�ܣ������û�����ȡ��֧��������ϵͳ���صĴ���
						//Toast.makeText(mContext, "֧��ʧ��",
						//		Toast.LENGTH_SHORT).show();
						AliPaying.this.finish();
						UniPaying.setMobilePayResult(2);
					}
				}
				break;
			}
			case SDK_CHECK_FLAG: {
//				Toast.makeText(mContext, "�����Ϊ��" + msg.obj,
//						Toast.LENGTH_SHORT).show();
				break;
			}
			default:
				break;
			}
		};
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		Intent intent = getIntent();
		order_id = intent.getStringExtra("order_id");
		money = intent.getExtras().getString("money");
		name = intent.getExtras().getString("name");
		Log.i("lvjian", "dddddddd----money===>" + money);
		Log.i("lvjian", "dddddddd----===>" + order_id);
		// �{��֧����
		
		pay();
	}
	
	/**
	 * call alipay sdk pay. ����SDK֧��
	 * 
	 */
	public void pay() {
		// ����
		String orderInfo = getNewOrderInfo();

		// �Զ�����RSA ǩ��
		String sign = sign2(orderInfo);
		try {
			// �����sign ��URL����
			sign = URLEncoder.encode(sign, "UTF-8");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}

		// �����ķ���֧���������淶�Ķ�����Ϣ
		final String payInfo = orderInfo + "&sign=\"" + sign + "\"&"
				+ getSignType();

		Runnable payRunnable = new Runnable() {

			@Override
			public void run() {
				try {
					// ����PayTask ����
					PayTask alipay = new PayTask(AliPaying.this);
					
					// ����֧���ӿڣ���ȡ֧�����
					String result = alipay.pay(payInfo);
					Message msg = new Message();
					msg.what = SDK_PAY_FLAG;
					msg.obj = result;
					mHandler.sendMessage(msg);
				}
				catch (Exception ex) {
					ex.printStackTrace();
				}
			}
		};

		// �����첽����
		Thread payThread = new Thread(payRunnable);
		payThread.start();
	}

	/**
	 * check whether the device has authentication alipay account.
	 * ��ѯ�ն��豸�Ƿ����֧������֤�˻�
	 * 
	 */
//	public void check(View v) {
//		Runnable checkRunnable = new Runnable() {
//
//			@Override
//			public void run() {
//				// ����PayTask ����
//				PayTask payTask = new PayTask(PayDemoActivity.this);
//				// ���ò�ѯ�ӿڣ���ȡ��ѯ���
//				boolean isExist = payTask.checkAccountIfExist();
//
//				Message msg = new Message();
//				msg.what = SDK_CHECK_FLAG;
//				msg.obj = isExist;
//				mHandler.sendMessage(msg);
//			}
//		};
//
//		Thread checkThread = new Thread(checkRunnable);
//		checkThread.start();
//
//	}

	/**
	 * get the sdk version. ��ȡSDK�汾��
	 * 
	 */
//	public void getSDKVersion() {
//		PayTask payTask = new PayTask(mContext);
//		String version = payTask.getVersion();
//		Toast.makeText(mContext, version, Toast.LENGTH_SHORT).show();
//	}

	/**
	 * create the order info. ����������Ϣ
	 * 
	 */
	public String getNewOrderInfo() {
		// ǩԼ���������ID
		String orderInfo = "partner=" + "\"" + Keys.DEFAULT_PARTNER + "\"";

		// ǩԼ����֧�����˺�
		orderInfo += "&seller_id=" + "\"" + Keys.DEFAULT_SELLER + "\"";

		// �̻���վΨһ������
		orderInfo += "&out_trade_no=" + "\"" + order_id + "\"";

		// ��Ʒ����
		orderInfo += "&subject=" + "\"" + name + "\"";

		// ��Ʒ����
		orderInfo += "&body=" + "\"" + "����Ҷһ��ֱ��ײ�" + "\"";

		// ��Ʒ���
		orderInfo += "&total_fee=" + "\"" + money + "\"";

		// �������첽֪ͨҳ��·��
//		orderInfo += "&notify_url=" + "\"" + "http://60.174.249.98:8001/api/pay/malipay/notify_url.php"
//				+ "\"";

		orderInfo += "&notify_url=" + "\"" + "http://www.wepoker.cn/api/pay/malipay/notify_url.php"+ "\"";
		
		// ����ӿ����ƣ� �̶�ֵ
		orderInfo += "&service=\"mobile.securitypay.pay\"";
		
		// ֧�����ͣ� �̶�ֵ
		orderInfo += "&payment_type=\"1\"";
		
		// �������룬 �̶�ֵ
		orderInfo += "&_input_charset=\"utf-8\"";

		// ����δ����׵ĳ�ʱʱ��
		// Ĭ��30���ӣ�һ����ʱ���ñʽ��׾ͻ��Զ����رա�
		// ȡֵ��Χ��1m��15d��
		// m-���ӣ�h-Сʱ��d-�죬1c-���죨���۽��׺�ʱ����������0��رգ���
		// �ò�����ֵ������С���㣬��1.5h����ת��Ϊ90m��
		orderInfo += "&it_b_pay=\"30m\"";

		// extern_tokenΪ���������Ȩ��ȡ����alipay_open_id,���ϴ˲����û���ʹ����Ȩ���˻�����֧��
		// orderInfo += "&extern_token=" + "\"" + extern_token + "\"";

		// ֧��������������󣬵�ǰҳ����ת���̻�ָ��ҳ���·�����ɿ�
		orderInfo += "&return_url=\"m.alipay.com\"";

		// �������п�֧���������ô˲���������ǩ���� �̶�ֵ ����ҪǩԼ���������п����֧��������ʹ�ã�
		// orderInfo += "&paymethod=\"expressGateway\"";

		return orderInfo;
	}

	/**
	 * sign the order info. �Զ�����Ϣ����ǩ��
	 * 
	 * @param content
	 *            ��ǩ��������Ϣ
	 */
	public String sign2(String content) {
		//return SignUtils.sign(content, Keys.PRIVATE);
		return Rsa.sign(content, Keys.PRIVATE);
	}

	/**
	 * get the sign type we use. ��ȡǩ����ʽ
	 * 
	 */
	public String getSignType() {
		return "sign_type=\"RSA\"";
	}

}
