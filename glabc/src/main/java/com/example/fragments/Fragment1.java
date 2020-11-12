package com.example.fragments;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.fragment.app.Fragment;

import com.example.glabc.R;

public class Fragment1 extends Fragment {
    private static String ARG_PARAM = "param_key";
    private String mParam;
    private Activity mActivity;
    public void onAttach(Context context) {
        //只有onCreateView()在重写时不用写super方法，其他生命周期重载方法都需要。
        super.onAttach(context);
        //如果要获取Activity对象，不建议调用getActivity()，而是在onAttach()中将Context对象强转为Activity对象。
        mActivity = (Activity) context;
        mParam = getArguments().getString(ARG_PARAM);  //获取参数
    }
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        /**
         * 该方法返回Fragment的UI布局，需要注意的是inflate()的第三个参数是false，
         * 因为在Fragment内部实现中，会把该布局添加到container中，如果设为true，那么就会重复做两次添加，则会抛异常
         */
        View root = inflater.inflate(R.layout.fragment_1, container, false);
        TextView view = root.findViewById(R.id.fragment1_text);
        view.setText(mParam);
        return root;
    }
    public static Fragment1 newInstance(String str) {
        Fragment1 fragment = new Fragment1();
        Bundle bundle = new Bundle();
        bundle.putString(ARG_PARAM, str);
        /**
         * 如果在创建Fragment时要传入参数，必须要通过setArguments(Bundle bundle)方式添加，
         * 而不建议通过为Fragment添加带参数的构造函数，因为通过setArguments()方式添加，
         * 在由于内存紧张导致Fragment被系统杀掉并恢复（re-instantiate）时能保留这些数据。
         * 官方建议如下：
         * It is strongly recommended that subclasses do not have other constructors with parameters,
         * since these constructors will not be called when the fragment is re-instantiated.
         */
        fragment.setArguments(bundle);   //设置参数
        return fragment;
    }
}
