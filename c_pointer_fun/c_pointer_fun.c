
acount_info_t *GetNum(); //指针函数声明形式  
  
acount_info_t *GetNum() {  
    //static int num[]={0,1,2,3,4,5,6}; 
    static acount_info_t a;
    
    strcpy(a.appkey, "22927");
    strcpy(a.appsecret, "3943c9913a370d2b0a005c9d0a0fc965251e1362f67e24d147b5d0688de4557a");
    strcpy(a.device_ID, "456123");
    strcpy(a.device_Type, "852963");

    return &a;  //返回一个地址  
}  
