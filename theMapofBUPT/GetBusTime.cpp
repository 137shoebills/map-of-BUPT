#include"time.h" 
#include<iostream>

using namespace std;
//假设已经到达公交车上车处，乘坐公交车,从校区A到B所用时间（秒数) 
 
long long GetSBusTimeAB(struct tm* now)
{
    int waitime; //表示需要等待的时间,单位为秒 
	int traveltime=3600; //路上花费时间,1h
	
	if(now->tm_wday==0||now->tm_wday==6)//如果在周日或周六，没有校车
	   return -1; 
	   
	else if(now->tm_wday==5) //如果在周五，少了一班车 
	{
    if(now->tm_hour<6||(now->tm_hour==6&&now->tm_min<=50)) //可以等待
	    waitime=(6-now->tm_hour)*3600+(50-now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<8||(now->tm_hour==8&&now->tm_min<=30))
	    waitime=(8-now->tm_hour)*3600+(30-now->tm_min)*60-(now->tm_sec);
    else if(now->tm_hour<12||(now->tm_hour==12&&now->tm_min==0))
	     waitime=(12-now->tm_hour)*3600-(now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<13||(now->tm_hour==13&&now->tm_min<=30)) //可以等待
	    waitime=(13-now->tm_hour)*3600+(30-now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<14||(now->tm_hour==14&&now->tm_min<=20))
	    waitime=(14-now->tm_hour)*3600+(20-now->tm_min)*60-(now->tm_sec);
	else 
	    return -1; //没车啦 
	}
	
	else//在周一到周四 
	{
	if(now->tm_hour<6||(now->tm_hour==6&&now->tm_min<=50)) //可以等待
	    waitime=(6-now->tm_hour)*3600+(50-now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<8||(now->tm_hour==8&&now->tm_min<=30))
	    waitime=(8-now->tm_hour)*3600+(30-now->tm_min)*60-(now->tm_sec);		
    else if(now->tm_hour<12||(now->tm_hour==12&&now->tm_min==0))
	     waitime=(12-now->tm_hour)*3600-(now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<13||(now->tm_hour==13&&now->tm_min<=30)) //可以等待
	    waitime=(13-now->tm_hour)*3600+(30-now->tm_min)*60-(now->tm_sec);
	else if(now->tm_hour<14||(now->tm_hour==14&&now->tm_min<=20))
	    waitime=(14-now->tm_hour)*3600+(20-now->tm_min)*60-(now->tm_sec);
 	else if(now->tm_hour<16||(now->tm_hour==16&&now->tm_min<=50))
         waitime=(16-now->tm_hour)*3600+(50-now->tm_min)*60-(now->tm_sec);

	else 
	    return -1; //没车啦 
	}
	 
    return waitime+traveltime; 
 } 
  
long long GetSBusTimeBA(struct tm* now)  //从校区B到校区A 
{
    int waitime; //表示需要等待的时间,单位为秒 
	int traveltime=3600; //路上花费时间 
	
	if(now->tm_wday==0||now->tm_wday==6)//如果在周日或周六，没有校车
	   return -1; 
	   
	else if(now->tm_wday==5) //如果在周五，少了一班车 
	{
	 if(now->tm_hour<9||(now->tm_hour==9&&now->tm_min<=50)) //可以等待
	    waitime=(9-now->tm_hour)*3600+(50-now->tm_min)*60-(now->tm_sec);
	    
	else if(now->tm_hour<11||(now->tm_hour==11&&now->tm_min<=40))
	    waitime=(11-now->tm_hour)*3600+(40-now->tm_min)*60-(now->tm_sec);
	    
    else if(now->tm_hour<13||(now->tm_hour==13&&now->tm_min==0))
	     waitime=(13-now->tm_hour)*3600-(now->tm_min)*60-(now->tm_sec);
	     
	else if(now->tm_hour<15||(now->tm_hour==15&&now->tm_min<=45)) //可以等待
	    waitime=(15-now->tm_hour)*3600+(45-now->tm_min)*60-(now->tm_sec);
	    
	else if(now->tm_hour<17||(now->tm_hour==17&&now->tm_min<=10))
	    waitime=(17-now->tm_hour)*3600+(10-now->tm_min)*60-(now->tm_sec);
	    
 	else if(now->tm_hour<18||(now->tm_hour==18&&now->tm_min<=25))
	    waitime=(18-now->tm_hour)*3600+(25-now->tm_min)*60-(now->tm_sec);
	    
	else 
	    return -1; //没车啦 
	}
	
	else//在周一到周四 
	{
	 if(now->tm_hour<9||(now->tm_hour==9&&now->tm_min<=50)) //可以等待
	    waitime=(9-now->tm_hour)*3600+(50-now->tm_min)*60-(now->tm_sec);
	    
	else if(now->tm_hour<11||(now->tm_hour==11&&now->tm_min<=40))
	    waitime=(11-now->tm_hour)*3600+(40-now->tm_min)*60-(now->tm_sec);
	    
    else if(now->tm_hour<13||(now->tm_hour==13&&now->tm_min==0))
	     waitime=(13-now->tm_hour)*3600-(now->tm_min)*60-(now->tm_sec);
	     
	else if(now->tm_hour<15||(now->tm_hour==15&&now->tm_min<=45)) //可以等待
	    waitime=(15-now->tm_hour)*3600+(45-now->tm_min)*60-(now->tm_sec);
	    
	else if(now->tm_hour<17||(now->tm_hour==17&&now->tm_min<=10))
	    waitime=(17-now->tm_hour)*3600+(10-now->tm_min)*60-(now->tm_sec);
	    
 	else if(now->tm_hour<18||(now->tm_hour==18&&now->tm_min<=25))
	    waitime=(18-now->tm_hour)*3600+(25-now->tm_min)*60-(now->tm_sec);
	  	    
 	else if(now->tm_hour<21||(now->tm_hour==21&&now->tm_min<=10))
	    waitime=(21-now->tm_hour)*3600+(10-now->tm_min)*60-(now->tm_sec);  
	    
	else 
	    return -1; //没车啦 
	}
	 
    return waitime+traveltime; 
 } 
 
 //认为两个校区周围公交车运行时间一样 
 //到达公交车上车处，等待并乘坐总共花的时间 
 long long GetBus(struct tm* now)
 {
 	int waitime; //表示需要等待的时间,单位为秒 
	int traveltime=5700; //路上花费时间,1h35min
	
	if(now->tm_hour<5||(now->tm_hour==5&&now->tm_min<=30)) 
	     waitime=(5-now->tm_hour)*3600+(30-now->tm_min)*60-(now->tm_sec); 
	else if(now->tm_hour==23&&now->tm_min>0)
	     return -1; //没车啦
	else
	{
	   	if(now->tm_min==0||now->tm_min==15||now->tm_min==30||now->tm_min==45)
	   	  waitime=0; 
	   	else if(now->tm_min>0&&now->tm_min<15)
	   	  waitime=15-now->tm_min;
	   	else if(now->tm_min>15&&now->tm_min<30)
	   	  waitime=30-now->tm_min;
	   	else if(now->tm_min>30&&now->tm_min<45)
	   	  waitime=45-now->tm_min;
	   	else 
	   	  waitime=60-now->tm_min;
	 } 
	return traveltime+waitime;
 }
 
/* int main()
 {
 	time_t t;
 	tm *tp;
 	t=time(NULL);
 	tp=localtime(&t);
 	long long time1=0,time2=0;
 	cout << tp->tm_mon+1<<' '<<tp->tm_wday<<' '<< tp->tm_year+1900<< endl;
 	cout << tp->tm_hour<<':'<<tp->tm_min<<':'<<tp->tm_sec<<endl;
	time1= GetSBusTimeAB(tp);
	time2= GetSBusTimeAB(tp);
	cout <<"time1 " << time1 << endl; 
	cout <<"time2 " << time2 << endl;
 	return 0;
}*/

//公交车和校内班车运行时的距离一样长？？？ 
//校区间求最短距离，只算走路还是算上车走的？？ 
