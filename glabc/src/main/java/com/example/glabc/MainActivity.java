package com.example.glabc;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.widget.TextViewCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.res.ColorStateList;
import android.graphics.Color;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Toolbar;

import com.example.fragments.Fragment1;
import com.example.fragments.Fragment2;
import com.example.fragments.Fragment3;
import com.example.fragments.Fragment4;
import com.google.android.material.navigation.NavigationView;


public class MainActivity extends AppCompatActivity {
    public final static int FRAGMENT_1 = 1,FRAGMENT_2=2,FRAGMENT_3=3,FRAGMENT_4=4;
    private enum FRAGMENTID{
        FRAGMENT1(R.id.single_1,FRAGMENT_1),
        FRAGMENT2(R.id.single_2,FRAGMENT_2),
        FRAGMENT3(R.id.single_3,FRAGMENT_3),
        FRAGMENT4(R.id.single_4,FRAGMENT_4);

//        private String name;
        private int menuiteid;
        private int position;
        FRAGMENTID(int menuiteid,int position){
            this.menuiteid = menuiteid;
            this.position = position;
        }
        public int getMenuiteid(){
            return menuiteid;
        }
        public int getPosition(){
            return position;
        }
        public static int getPositonforItemId(int menuiteid){
            if(menuiteid == FRAGMENT1.menuiteid){
                return FRAGMENT1.getPosition();
            }else if(menuiteid == FRAGMENT2.menuiteid){
                return FRAGMENT2.getPosition();
            }else if(menuiteid == FRAGMENT3.menuiteid){
                return FRAGMENT3.getPosition();
            }else if(menuiteid == FRAGMENT4.menuiteid){
                return FRAGMENT4.getPosition();
            }
            return 1;
        }
        public static int getItemIdforPositon(int position){
            if(position == FRAGMENT1.position){
                return FRAGMENT1.getMenuiteid();
            }else if(position == FRAGMENT2.position){
                return FRAGMENT2.getMenuiteid();
            }else if(position == FRAGMENT3.position){
                return FRAGMENT3.getMenuiteid();
            }else if(position == FRAGMENT4.position){
                return FRAGMENT4.getMenuiteid();
            }
            return R.id.single_1;
        }
    }
    private MenuItem item1,item2,item3,item4;
    private FragmentManager fragmentManager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        fragmentManager = getSupportFragmentManager();

        NavigationView navigationView = findViewById(R.id.navigation_view);
        View headerlayout = navigationView.getHeaderView(0);
        //头像点击事件
        TextView headertextview = headerlayout.findViewById(R.id.header_tv);
        headertextview.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                XLog.LogOut("headertextview clicked!");
                Toast.makeText(getApplicationContext(), "头像", Toast.LENGTH_SHORT).show();
            }
        });

        item1 = (MenuItem) navigationView.getMenu().findItem(R.id.single_1);
        item2 = (MenuItem) navigationView.getMenu().findItem(R.id.single_2);
        item3 = (MenuItem) navigationView.getMenu().findItem(R.id.single_3);
        item4 = (MenuItem) navigationView.getMenu().findItem(R.id.single_4);



        //设置item 消息数量信息
        LinearLayout siglelayout = (LinearLayout) item1.getActionView();
        TextView msg= (TextView) siglelayout.findViewById(R.id.msg_bg);
        msg.setText("99+");


        //设置条目点击监听
        navigationView.setNavigationItemSelectedListener(new NavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
                //安卓
                Toast.makeText(getApplicationContext(), menuItem.getTitle(), Toast.LENGTH_SHORT).show();
                //设置哪个按钮被选中
//                menuItem.setChecked(true);
                //关闭侧边栏
//                drawer.closeDrawers();
                position =FRAGMENTID.getPositonforItemId(menuItem.getItemId());
                setTabSelection(position);
                MenuItemSelect(menuItem);
                return false;
            }
        });

        //button事件的监听
        Button bt_setting = findViewById(R.id.footer_item_setting);
        bt_setting.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "设置", Toast.LENGTH_SHORT).show();
            }
        });
        Button bt_quit = findViewById(R.id.footer_item_out);
        bt_quit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "退出", Toast.LENGTH_SHORT).show();
            }
        });

        UIInit(navigationView);

    }
    private void UIInit(NavigationView navigationView){
        setTabSelection(position);
        MenuItem item = (MenuItem) navigationView.getMenu().findItem(FRAGMENTID.getItemIdforPositon(position));
        MenuItemSelect(item);
    }

    /**
     * menuitem 选中状态设置
     * @param menuItem
     */
    private void MenuItemSelect(MenuItem menuItem){
        if(menuItem != null && !menuItem.getTitle().toString().contains(">> "))
        menuItem.setTitle(">> "+menuItem.getTitle()+" <<");
    }

    /**
     * menuItem 取消选中状态
     * @param menuItem
     */
    private void MenuItemUnSelect(MenuItem menuItem){
        if(menuItem != null)
            menuItem.setTitle(menuItem.getTitle().toString().replace(">> ","").replace(" <<",""));

    }

    /**
     * 取消所有 menuItem 的选中状态
     */
    private void CancelAllMenuItemSelect(){
        MenuItemUnSelect(item1);
        MenuItemUnSelect(item2);
        MenuItemUnSelect(item3);
        MenuItemUnSelect(item4);    }


    private Fragment fragment1,fragment2,fragment3,fragment4;

    /**
     * 多个fragment的切换
     */
    private void setTabSelection(int position) {
        //记录position
        this.position = position;
        //更改底部导航栏按钮状态
//        changeButtonStatus(position);
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        // 先隐藏掉所有的Fragment，以防止有多个Fragment显示在界面上的情况
        hideFragments(transaction);
        //ui选择状态取消
        CancelAllMenuItemSelect();
        switch (position) {
            case FRAGMENT_1:
                if (fragment1 == null) {
                    /**
                     * add()是对Fragment众多操作中的一种，还有remove(), replace()等，
                     * 功能是：添加并显示
                     * 第一个参数是根容器的id（FrameLayout的id，即”@id/container”），
                     * 第二个参数是Fragment对象，第三个参数是fragment的tag名，
                     * 指定tag的好处是后续我们可以通过
                     * Fragment1 frag = getSupportFragmentManager().findFragmentByTag("f1")
                     * 从FragmentManager中查找Fragment对象。
                     */
                    fragment1 =  Fragment1.newInstance("fragment 1");
                    transaction.add(R.id.container,fragment1, "f1");//.addToBackStack("fname")
                } else {
                    transaction.show(fragment1);
                }
                break;
            case FRAGMENT_2:
                if (fragment2 == null) {
                    fragment2 = Fragment2.newInstance("fragment 2");
                    transaction.add(R.id.container, fragment2, "f2");//.addToBackStack("fname")
                } else {
                    transaction.show(fragment2);
                }
                break;
            case FRAGMENT_3:
                if (fragment3 == null) {
                    fragment3 = Fragment3.newInstance("fragment 3");
                    transaction.add(R.id.container, fragment3, "f3");//.addToBackStack("fname")
                } else {
                    transaction.show(fragment3);
                }
                break;
            case FRAGMENT_4:
                if (fragment4 == null) {
                    fragment4 = Fragment4.newInstance("fragment 4");
                    transaction.add(R.id.container, fragment4, "f4");//.addToBackStack("fname")
                } else {
                    transaction.show(fragment4);
                }
                break;
        }
        transaction.commitAllowingStateLoss();
    }

    private void hideFragments(FragmentTransaction transaction){
        if(fragment1 != null){
            transaction.hide(fragment1);
        }
        if(fragment2 != null){
            transaction.hide(fragment2);
        }
        if(fragment3 != null){
            transaction.hide(fragment3);
        }
        if(fragment4 != null){
            transaction.hide(fragment4);
        }
    }

    /**
     * 当转跳到其他Activity、打开多任务窗口、使用Home回到主屏幕再返回时
     * 需要记录当前fragment，
     * @param savedInstanceState
     */
    //记录MenuItem id 和 Fragment position的相同标号
    private int position = 1;
    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        //取出保存的 "position" 然后切换到相应的fragment
        position = savedInstanceState.getInt("position");
        setTabSelection(position);
        super.onRestoreInstanceState(savedInstanceState);
    }

    @Override
    public void onSaveInstanceState(@NonNull Bundle outState, @NonNull PersistableBundle outPersistentState) {
       // 这句话导致了重影的出现，于是我删除了这句话，
//        super.onSaveInstanceState(outState, outPersistentState);
        //记录当前的position
        outState.putInt("position", position);
    }
}
