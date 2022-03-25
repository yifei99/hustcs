/*Passenger*/
create TABLE Passenger(
PCardID char(18) PRIMARY KEY,
PName char(20),
Sex bit check (Sex=0 or Sex=1),
Age smallint
)
/*Station*/
create TABLE Station(
SID int PRIMARY KEY,
SName char(20),
CityName char(20)
)
/*Train*/
create TABLE Train(
TID int PRIMARY KEY,
SDATE date,
TName char(20),
SStationID int FOREIGN KEY REFERENCES Station(SID),
AStationID int FOREIGN KEY REFERENCES Station(SID),
STime datetime,
ATime datetime,
)
/*TrainPass*/
create TABLE TrainPass(
TID int,
SNO smallint,
SID int FOREIGN KEY REFERENCES STation(SID),
STime datetime,
ATime datetime,
PRIMARY KEY(TID,SNO)
)
/*TakeTrainRecord*/
create TABLE TakeTrainRecord(
RID int PRIMARY KEY,
PCardId char(18) FOREIGN KEY REFERENCES Passenger(PCardID),
TID int FOREIGN KEY REFERENCES Train(TID),
SStationID int FOREIGN KEY REFERENCES Station(SID),
AStationID int FOREIGN KEY REFERENCES Station(SID),
CarrigeID smallint,
SeatRow smallint,
SeatNo char(1) check(SeatNo in('A','B','C','D','E')),
SStatus int check (SStatus in (0,1,2))
)
/*DiagnoseRecord*/
create TABLE DiagnoseRecord(
DID int PRIMARY KEY,
PCardID char(18) FOREIGN KEY REFERENCES Passenger(PCardID),
DDay date,
DStatus smallint check(DStatus in (1,2,3)),
FDay date
)
/*TrainContactor*/
create TABLE TrainContactor(
CDate date,
CCardID char(18),
DStatus smallint check (DStatus in (1,2,3)),
PCardID char(18),
PRIMARY KEY(CDate,CCardID,DStatus,PCardID)
)

/*增*/
insert into TakeTrainRecord(RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatRow,SeatNo,SStatus) 
VALUES(33,'11011619880513219X',105,129,470,2,2,'A',0)
/*改*/
update TakeTrainRecord set SStatus=1
where RID=33
/*删*/
delete from TakeTrainRecord
where RID=33
/*批处理操作*/
create table WH_TakeTrainRecord(
   RID int PRIMARY KEY,
   PCardID char(18) REFERENCES Passenger(PCardID),
   TID int REFERENCES Train(TID),
   SStationID int REFERENCES Station(SID),
   AStationID int REFERENCES Station(SID),
   CarrigeID smallint,
   SeatRow smallint,
   SeatNo  char(1),
   SStatus int
)
INSERT INTO WH_TakeTrainRecord(RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatNo,SeatRow,SStatus) 
SELECT RID,PCardID,TID,SStationID,AStationID,CarrigeID,SeatNo,SeatRow,SStatus 
FROM TakeTrainRecord 
WHERE SStationID BETWEEN 1593 AND 1616
/*创建视图*/
create view view_diagnose
as
  select DiagnoseRecord.PCardID,PName,Sex,TakeTrainRecord.TID,SDATE,CarrigeID,SeatRow,SeatNo
  from Passenger,TakeTrainRecord,Train,DiagnoseRecord
  where Passenger.PCardID=TakeTrainRecord.PCardID
  and Passenger.PCardID=DiagnoseRecord.PCardID
  and TakeTrainRecord.PCardID=DiagnoseRecord.PCardID
  and TakeTrainRecord.TID=Train.TID
  and DiagnoseRecord.DStatus=1
  and TakeTrainRecord.SStatus=1
go
/*触发器
create trigger newpatient
on DiagnoseRecord
after insert
as
begin
insert into TrainContactor(CDate,CCardID,DStatus,PCardID)
select	Train.SDATE,DiagnoseRecord.PCardID,2,TakeTrainRecord.PCardID
FROM DiagnoseRecord,TakeTrainRecord,Train
WHERE DiagnoseRecord.DStatus=1
and DiagnoseRecord.PCardID=TakeTrainRecord.PCardID
and TakeTrainRecord.TID=Train.TID
and 
end

create trigger newcontactor
on DiagnoseRecord
after insert
as
begin

end
*/

/*1.查询确诊者“张三”的在发病前14天内的乘车记录*/
select TakeTrainRecord.*
from TakeTrainRecord,Passenger,Train,DiagnoseRecord
where TakeTrainRecord.PCardID=Passenger.PCardID 
and Passenger.PName='张三'
and TakeTrainRecord.TID=train.TID 
and DiagnoseRecord.PCardID=Passenger.PCardID
and Train.SDate
between DATEADD(DAY,-15,DiagnoseRecord.FDay) and DiagnoseRecord.FDay
/*2.查询所有从城市“武汉”出发的乘客乘列车所到达的城市名*/
select  s2.cityname
from TakeTrainRecord ,Station s1 ,Station s2
where TakeTrainRecord.SStationID=s1.SID
and  TakeTrainRecord.AStationID=s2.SID
and s1.CityName='武汉' 
/*3.计算每位新冠患者从发病到确诊的时间间隔（天数）及患者身份信息，并将结果按照发病时间天数的降序排列*/
select Passenger.*,data=DATEDIFF("d",DiagnoseRecord.FDay,DiagnoseRecord.DDay)
from DiagnoseRecord,Passenger
where DiagnoseRecord.DStatus=1
and DiagnoseRecord.PCardID=Passenger.PCardID
order by DATEDIFF("d",DiagnoseRecord.FDay,DiagnoseRecord.DDay) DESC;
/*4.查询“2020-01-22”从“武汉”发出的所有列车*/
select Train.TName
from Train,Station
where Train.SDATE='2020-1-22'
and Train.SStationID=Station.SID
and Station.CityName='武汉';
/*5.查询“2020-01-27”途经“武汉”的所有列车*/
select Train.TName
from TrainPass,Station,Train
where TrainPass.SID = Station.SID
and Station.CityName='武汉'
and TrainPass.TID=Train.TID
and TrainPass.STime >='2020-01-27 00:00:00.000'and TrainPass.STIME<='2020-01-28 00:00:00.000'
/*6.查询“2020-01-22”从武汉离开的所有乘客的身份证号、所到达的城市、到达日期*/
select Passenger.PCardID,astation.CityName,atrainpass.STime
from Passenger,Station sstation,Station astation,TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='武汉'
and strainpass.Atime >='2020-01-22 00:00:00.000' and strainpass.ATime<='2020-01-23 00:00:00.000';
/*7.统计“2020-01-22” 从武汉离开的所有乘客所到达的城市及达到各个城市的武汉人员数*/
select astation.CityName,count( *) as sum
from Passenger,Station sstation,Station astation,
TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='武汉'
and strainpass.Atime >='2020-01-22 00:00:00.000' and strainpass.ATime<='2020-01-23 00:00:00.000'
group by astation.CityName;
/*8.查询2020年1月到达武汉的所有人员*/
select Passenger.PName
from TakeTrainRecord,Station,TrainPass,Passenger
where Station.SID=TakeTrainRecord.AStationID
and Passenger.PCardID=TakeTrainRecord.PCardID
and Station.CityName='武汉'
and TrainPass.TID=TakeTrainRecord.TID
and TrainPass.SID=TakeTrainRecord.SStationID
and TrainPass.ATime between '2020-01-01' and '2020-01-31';
/*9.查询2020年1月乘车途径武汉的外地人员（身份证非“420”开头）*/
select distinct Passenger.PName
from (select  TrainPass.TID,SNo
from TrainPass,Station
where TrainPass.SID=Station.SID
and Station.CityName='武汉'
and TrainPass.STime between '2020-1-1'and'2020-1-31')
as passbywh(tid,sno),TakeTrainRecord,Passenger,TrainPass snum,TrainPass anum
where TakeTrainRecord.TID = passbywh.tid
and snum.TID=TakeTrainRecord.TID
and	snum.SID=TakeTrainRecord.SStationID
and anum.TID=TakeTrainRecord.TID
and	anum.SID=TakeTrainRecord.AStationID
and passbywh.sno between snum.SNo and anum.SNo
and Passenger.PCardID=TakeTrainRecord.PCardID
and Passenger.PCardID not like '420%';
/*10.统计“2020-01-22”乘坐过‘G007’号列车的新冠患者在火车上的密切接触乘客人数（每位新冠患者的同车厢人员都算同车密切接触）*/
select count(distinct p1.PName) as sum 
from Passenger p1,Passenger p2,TakeTrainRecord t1,TakeTrainRecord t2,DiagnoseRecord,Train
where p2.PCardID=t2.PCardID 
and Train.TID=t2.TID 
and Train.TName='G007'
and Train.SDate='2020-01-22' 
and t2.SStatus=1  
and p1.PCardID=t1.PCardID 
and Train.TID=t1.TID 
and Train.TName='G007' 
and Train.SDate='2020-01-22' 
and t1.SStatus=1 
and p2.PCardID=DiagnoseRecord.PCardID 
and DiagnoseRecord.DStatus=1 
and t1.CarrigeID=t2.CarrigeID
/*11.查询一趟列车的一节车厢中有3人及以上乘客被确认患上新冠的列车名、出发日期，车厢号*/
select Train.TName,Train.SDATE,inftrain.CarrigeID
from Train, (select TakeTrainRecord.TID,TakeTrainRecord.CarrigeID
from TakeTrainRecord,DiagnoseRecord
where TakeTrainRecord.PCardID=DiagnoseRecord.PCardID
and DiagnoseRecord.DStatus=1
group by TakeTrainRecord.TID,TakeTrainRecord.CarrigeID
having count(*)>2) 
as inftrain
where Train.TID=inftrain.TID;
/*12.查询没有感染任何周边乘客的新冠乘客的身份证号、姓名、乘车日期*/
select DISTINCT Passenger.PCardID,PName,leavetime=TrainPass.ATime
from Passenger,TakeTrainRecord,TrainPass,DiagnoseRecord,TrainContactor
where Passenger.PCardID=TakeTrainRecord.PCardID
and TakeTrainRecord.SStatus=1
and Passenger.PCardID=DiagnoseRecord.PCardID
and DiagnoseRecord.DStatus=1
and Passenger.PCardID=TrainContactor.PCardID
and TrainContactor.DStatus=3
and TakeTrainRecord.TID=TrainPass.TID
and TakeTrainRecord.SStationID=TrainPass.SID
/*13.查询到达 “北京”、或“上海”，或“广州”（即终点站）的列车名，要求where子句中除了连接条件只能有一个条件表达式*/
select Train.TName,Station.CityName
from Train,Station
where Station.SID=Train.AStationID
and Station.CityName in('上海','北京','广州')
/*14.查询“2020-01-22”从“武汉站”出发，然后当天换乘另一趟车的乘客身份证号和首乘车次号，结果按照首乘车次号降序排列，同车次则按照乘客身份证号升序排列*/
select fromwh.PName,fromwh.PCardID,fromwh.TID
from TakeTrainRecord,Station,
(select Passenger.PCardID,Passenger.PName,strainpass.TID
from Passenger,Station sstation,Station astation,TrainPass strainpass,TrainPass atrainpass,TakeTrainRecord
where Passenger.PCardID=TakeTrainRecord.PCardID
and sstation.SID=TakeTrainRecord.SStationID
and astation.SID=TakeTrainRecord.AStationID
and strainpass.TID=TakeTrainRecord.TID
and strainpass.SID=TakeTrainRecord.SStationID
and atrainpass.TID=TakeTrainRecord.TID
and atrainpass.SID=TakeTrainRecord.AStationID
and sstation.CityName='武汉'
and strainpass.ATime between '2020-1-22' and '2020-1-23') as fromwh
where TakeTrainRecord.SStationID=Station.SID
and station.cityname!='武汉'
and TakeTrainRecord.PCardID=fromwh.PCardID
order by fromwh.TID desc,fromwh.PCardID
/*15.查询所有新冠患者的身份证号，姓名及其2020年以来所乘坐过的列车名、发车日期，要求即使该患者未乘坐过任何列车也要列出来*/
select Passenger.PName,Passenger.PCardID,Train.TName,Train.SDate
from Passenger left join TakeTrainRecord on Passenger.PCardID=TakeTrainRecord.PCardID 
left join Train on Train.TID=TakeTrainRecord.TID
and Train.ATime between '2020.1.1' and  '2020.12.31'
inner join DiagnoseRecord on DiagnoseRecord.PCardID=Passenger.PCardID 
and DiagnoseRecord.DStatus=1
/*16.查询所有发病日期相同而且确诊日期相同的病患统计信息，包括：发病日期、确诊日期和患者人数，结果按照发病日期降序排列的前提下再按照确诊日期降序排列*/
select d1.DDay,d1.FDay ,count (*) as sum 
from DiagnoseRecord d1 where d1.DStatus=1
group by d1.DDay ,d1.FDay
order by d1.DDay desc ,d1.FDay desc