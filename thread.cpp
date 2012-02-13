#include "thread.h"

Thread::Thread()
{
}

void Thread::run()
{
        QFile file("/opt/Sinfo/service.ini");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        qDebug()<<"No find /opt/Sinfo/service.ini";
        return;
        }
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString tmp_str=in.readLine();
            QStringList tmp_list;
            tmp_list=tmp_str.split(tr("£º"));
            items.append(tmp_list.at(0));
            if(tmp_list.size()>0)
            {
            explains.append(tmp_list.at(1));
             }
                 }
        file.close();
     int i;
     QString program;
     for(i=0;i<items.size();i++)
     {
         int curint=768;
         if(this->items.at(i)=="readahead_early")
         {curint=0;}
         if(this->items.at(i)=="readahead_later")
         {curint=0;}
         if(this->items.at(i)=="ntpdate")
         {curint=0;}
         if(this->items.at(i)=="kudzu")
         {curint=0;}
         if(this->items.at(i)=="udev-post")
         {curint=0;}
         if(this->items.at(i)=="bluetooth")
         {curint=0;}
         if(this->items.at(i)=="dkms_autoinstaller")
         {curint=0;}
         if(this->items.at(i)=="iscsi")
         {curint=0;}
         if(this->items.at(i)=="gnokii-smsd")
         {curint=0;}
         if(this->items.at(i)=="rpcgssd")
         {curint=0;}
         if(this->items.at(i)=="lm_sensors")
         {curint=256;}
         program="service "+this->items.at(i)+" status";
         char buf[128];
         FILE *pp;
         QString currs;
         if((pp=popen(program.toAscii().data(),"r"))!=NULL)
         {
             while(fgets(buf,sizeof(buf),pp))
                   {
                     currs=tr(buf);
                     if(currs.indexOf(tr("ÔËÐÐ"))!=-1)
                     {curint=0;}
                     if(currs.indexOf(tr("ÒÑÍ£"))!=-1)
                     {curint=256;}
                     if(currs.indexOf(tr("×¢²á"))!=-1)
                     {curint=0;}
                     if(currs.indexOf("running")!=-1)
                     {curint=0;}
                     if(currs.indexOf("enabled")!=-1)
                     {curint=0;}
                     if(currs.indexOf("disabled")!=-1)
                     {curint=256;}
                     if(currs.indexOf("policy ACCEPT")!=-1)
                     {curint=0;}
                     if(currs.indexOf("CPU Temperature")!=-1)
                     {curint=0;}
                     if(currs.indexOf("stopped")!=-1)
                     {curint=256;}
                     if(currs.indexOf("lo eth0 ppp0")!=-1)
                     {curint=0;}
                     if(currs.indexOf("ok")!=-1)
                     {curint=0;}
                     if(currs.indexOf("driver loaded")!=-1)
                     {curint=0;}
                     if(currs.indexOf("not loaded")!=-1)
                     {curint=256;}
                     if(currs.indexOf("coretemp-isa-0000")!=-1)
                     {curint=0;}
                                 }
             pclose(pp);
         }
         status[i]=curint;
       }
}
