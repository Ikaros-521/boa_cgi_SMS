$(document).ready(function(){
	check_session();
	/*
	var text = sessionStorage.getItem('username');
	var pas = sessionStorage.getItem('password');
	if(pas != "true")
	{
		window.location.href="login_interface.html";
	}
	*/
	init_data();
	get_info();
	$("#input_page").keydown(function(e) {  
		if (e.keyCode == 13) {  
			jumpPage2();
		}  
	});
});


// check session
function check_session() {
	//$.alertable.alert('You Clicked OK');
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入str
			var str = xmlhttp.responseText;
			if(str.length == 0)
			{
				return;
			}
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var ret = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(ret.length == 0)
			{
				//my_alert(ret);
			}
			else
			{
				if(ret.indexOf("error") != -1)
				{
					my_alert(ret);
				}
				else if(ret.indexOf("failed") != -1)
				{
					sessionStorage.clear();
					window.parent.jump_to_login();
				}
				else if(ret.indexOf("success") != -1)
				{
				
				}
			}
			
			//alert("json:"+jsonstr);
			// 将jsonstr转换为json对象 json
		}
	}
	var sec = sessionStorage.getItem('sec');
	var session_id = sessionStorage.getItem('session_id');
	xmlhttp.open("GET","cgi-bin/check_session.cgi?check,sec:"+sec+",session_id:"+session_id+",",true);
	xmlhttp.send();
}

// 日历控件初始化
function init_data() {
	var date = new Date();
	var year = date.getFullYear();
	var month = date.getMonth() + 1;
	var day = date.getDate();
	if (month < 10) {
		month = "0" + month;
	}
	if (day < 10) {
		day = "0" + day;
	}
	var nowDate = year + "-" + month + "-" + day;
	//alert(nowDate);
	document.getElementById("data_start").value = "2020-01-01";
	document.getElementById("data_end").value = nowDate;
}

var pageSize=0;//每页显示行数
var currentPage_=1;//当前页全局变量，用于跳转时判断是否在相同页，在就不跳，否则跳转。
var totalPage;//总页数
var totalTr;//总行数

// 设置select
function setJumpPage() {
	var tempOption="";
	for(var i=1;i<=totalPage;i++)
	{
		tempOption+='<option value='+i+'>'+i+'</option>'
	}
	$("#jumpWhere").html(tempOption);
}
 
//跳转页面
function goPage(pno,psize){

	var itable = document.getElementById("listbody");
	var num = itable.rows.length;//表格所有行数(所有记录数)
	totalTr = num;
	//alert(num);
 
	pageSize = psize;//每页显示行数
    //总共分几页 
	if(num/pageSize > parseInt(num/pageSize)){   
		totalPage=parseInt(num/pageSize)+1;   
	}else{   
		totalPage=parseInt(num/pageSize);   
	}   
	var currentPage = pno;//当前页数
	currentPage_=currentPage;
	var startRow = (currentPage - 1) * pageSize+1; 
	var endRow = currentPage * pageSize;
	endRow = (endRow > num)? num : endRow;    
	//遍历显示数据实现分页
	/*for(var i=1;i<(num+1);i++){    
		var irow = itable.rows[i-1];
		if(i>=startRow && i<=endRow){
			irow.style.display = "";    
		}else{
			irow.style.display = "none";
		}
	}*/
 
	$("#listbody tr").hide();
	for(var i=startRow-1;i<endRow;i++)
	{
		$("#listbody tr").eq(i).show();
	}
	
	//var tempStr = "共"+num+"条 "+ pageSize + "条/页 共"+totalPage+"页 当前第"+currentPage+"页";
	//document.getElementById("barcon1").innerHTML = tempStr;
	document.getElementById("total_tr").innerHTML = "共"+num+"条";
	document.getElementById("paging").value = pageSize+"条/页";
	document.getElementById("total_page").innerHTML = "共"+totalPage+"页";
	
     
	if(currentPage>1){
		$("#firstPage").on("click",function(){
			goPage(1,psize);
		}).removeClass("ban");
		$("#prePage").on("click",function(){
			goPage(currentPage-1,psize);
		}).removeClass("ban");   
	}else{
		$("#firstPage").off("click").addClass("ban");
		$("#prePage").off("click").addClass("ban");  
	}
 
	if(currentPage<totalPage){
		$("#nextPage").on("click",function(){
			goPage(currentPage+1,psize);
		}).removeClass("ban")
		$("#lastPage").on("click",function(){
			goPage(totalPage,psize);
		}).removeClass("ban")
	}else{
		$("#nextPage").off("click").addClass("ban");
		$("#lastPage").off("click").addClass("ban");
	}   
    
	//$("#jumpWhere").val(currentPage);
	$("#input_page").val(currentPage);
}
 
// 检验非0的正整数
function check_num(str) {
	var reg = /^\+?[1-9][0-9]*$/;
	if (!reg.test(str)) {
		return false;
	}
	return true;
}
 
// 跳转按钮
function jumpPage()
{
	if(false == check_num($("#jumpWhere").val()))
	{
		alert("请输入非零的正整数");
	}
	else
	{
		var num = parseInt($("#jumpWhere").val());
		//alert(num);
		if(num != currentPage_)
		{
			if(num > totalPage)
			{
				alert("超出最大页数，请重新输入");
			}
			else
			{
				goPage(num,pageSize);
			}
		}
	}
}

function jumpPage2()
{
	if(false == check_num($("#input_page").val()))
	{
		alert("请输入非零的正整数");
	}
	else
	{
		var num = parseInt($("#input_page").val());
		//alert(num);
		if(num != currentPage_)
		{
			if(num > totalPage)
			{
				alert("超出最大页数，请重新输入");
			}
			else
			{
				goPage(num,pageSize);
			}
		}
	}
}

// 查询 日志信息
function query_info() {
	var start = document.getElementById("data_start");  
	var end = document.getElementById("data_end");
	//alert(start.value);
	$('#table1 tbody').html('');
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入str
			var str = xmlhttp.responseText;
			if(str.length == 0)
			{
				return;
			}
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var jsonstr = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(jsonstr.length == 0)
			{
				
			}
			else
			{
				//alert("json:"+jsonstr);
				// 将jsonstr转换为json对象 json
				var json = JSON.parse(jsonstr);
				//alert(json["A"]);
				//alert("调用get_json,传参json对象");
				get_json(json);
			}
		}
	}
	xmlhttp.open("GET","cgi-bin/get_log.cgi?get_info,start:log"+start.value+".log,end:log"+end.value+".log,",true);
	xmlhttp.send();
}

// 重置按钮
function reset() {
	init_data();
	get_info();
}


// 添加表格
function addlist(time, page, describe){  
	//创建一个tr  
	var tr = document.createElement("tr");  
	//创建td   
	  
	var td1 = document.createElement("td");  
	td1.innerHTML = time;  
	  
	var td2 = document.createElement("td");  
	td2.innerHTML = page; 
	  
	var td3 = document.createElement("td");  
	td3.innerHTML = describe;  
	  
	//将创建的td添加到tr中  
	tr.appendChild(td1);  
	tr.appendChild(td2);
	tr.appendChild(td3);  
	  
	//使用appendChild（tr）方法，将tr添加到listbody中  
	//其中获取的listbody是要将表格添加的位置的id  
	var listbody = document.getElementById("listbody");  
	listbody.appendChild(tr);  
};

// 解析json对象
function get_json(json) {
	//alert("进入get_json函数");

	for(var i = 0; i<json.length; i++){
		addlist(json[i].time,json[i].page,json[i].describe);
	//alert(json[i].time+","+json[i].page+","+json[i].describe);
	}
	//alert("get_json运行完毕");
	goPage(1,15);
	//setJumpPage();
};

// 获取日志信息
function get_info()
{
	$('#table1 tbody').html('');
	var xmlhttp;
	if(window.XMLHttpRequest)
	{
		//code for IE7+,Firefox,Chrome,Opera,Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{
		//code for IE6,IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if(xmlhttp.readyState==4 && xmlhttp.status==200)
		{
			//将接收到的字符串存入str
			var str = xmlhttp.responseText;
			if(str.length == 0)
			{
				return;
			}
			// 解决XML， 解析错误：语法错误
			try //Internet Explorer
			{
				xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
				xmlDoc.async = "false";
				xmlDoc.loadXML(text);
			} catch (e) {
				try //Firefox, Mozilla, Opera, etc.
				{
					parser = new DOMParser();
					xmlDoc = parser.parseFromString(str, "text/xml");
				} catch (e) { alert(e.message) }
			}

			var jsonstr = xmlDoc.getElementsByTagName('p')[0].textContent;
			if(jsonstr.length == 0)
			{
				
			}
			else
			{
				//alert("json:"+jsonstr);
				// 将jsonstr转换为json对象 json
				var json = JSON.parse(jsonstr);
				//alert(json["A"]);
				//alert("调用get_json,传参json对象");
				get_json(json);
			}
		}
	}
	var start = document.getElementById("data_start").value;
	var end = document.getElementById("data_end").value;
	xmlhttp.open("GET","cgi-bin/get_log.cgi?get_info,start:log"+start+".log,end:log"+end+".log,",true);
	xmlhttp.send();
};


// 日历
$(function () {
$('.J-datepicker-time').datePicker({
format: 'HH:mm:ss',
min: '04:23:11'
});
$('.J-datepicker-time-range').datePicker({
format: 'HH:mm:ss',
isRange: true,
min: '04:23:11',
max: '20:59:59'
});

var DATAPICKERAPI = {
activeMonthRange: function () {
return {
begin: moment().set({ 'date': 1, 'hour': 0, 'minute': 0, 'second': 0 }).format('YYYY-MM-DD HH:mm:ss'),
end: moment().set({ 'hour': 23, 'minute': 59, 'second': 59 }).format('YYYY-MM-DD HH:mm:ss')
}
},
shortcutMonth: function () {
var nowDay = moment().get('date');
var prevMonthFirstDay = moment().subtract(1, 'months').set({ 'date': 1 });
var prevMonthDay = moment().diff(prevMonthFirstDay, 'days');
return {
now: '-' + nowDay + ',0',
prev: '-' + prevMonthDay + ',-' + nowDay
}
},
shortcutPrevHours: function (hour) {
var nowDay = moment().get('date');
var prevHours = moment().subtract(hour, 'hours');
var prevDate = prevHours.get('date') - nowDay;
var nowTime = moment().format('HH:mm:ss');
var prevTime = prevHours.format('HH:mm:ss');
return {
day: prevDate + ',0',
time: prevTime + ',' + nowTime,
name: 'Nearly ' + hour + ' Hours'
}
},
rangeMonthShortcutOption1: function () {
var result = DATAPICKERAPI.shortcutMonth();
var resultTime = DATAPICKERAPI.shortcutPrevHours(18);
return [{
name: 'Yesterday',
day: '-1,-1',
time: '00:00:00,23:59:59'
}, {
name: 'This Month',
day: result.now,
time: '00:00:00,'
}, {
name: 'Lasy Month',
day: result.prev,
time: '00:00:00,23:59:59'
}, {
name: resultTime.name,
day: resultTime.day,
time: resultTime.time
}];
},
rangeShortcutOption1: [{
name: 'Last week',
day: '-7,0'
}, {
name: 'Last Month',
day: '-30,0'
}, {
name: 'Last Three Months',
day: '-90, 0'
}],
singleShortcutOptions1: [{
name: 'Today',
day: '0',
time: '00:00:00'
}, {
name: 'Yesterday',
day: '-1',
time: '00:00:00'
}, {
name: 'One Week Ago',
day: '-7'
}]
};
$('.J-datepicker').datePicker({
hasShortcut: true,
min: '2018-01-01 04:00:00',
max: '2029-10-29 20:59:59',
shortcutOptions: [{
name: 'Today',
day: '0'
}, {
name: 'Yesterday',
day: '-1',
time: '00:00:00'
}, {
name: 'One Week Ago',
day: '-7'
}],
hide: function () {
console.info(this)
}
});


$('.J-datepicker-day').datePicker({
hasShortcut: true,
shortcutOptions: [{
name: 'Today',
day: '0'
}, {
name: 'Yesterday',
day: '-1'
}, {
name: 'One week ago',
day: '-7'
}]
});


$('.J-datepicker-range-day').datePicker({
hasShortcut: true,
format: 'YYYY-MM-DD',
isRange: true,
shortcutOptions: DATAPICKERAPI.rangeShortcutOption1
});


$('.J-datepickerTime-single').datePicker({
format: 'YYYY-MM-DD HH:mm'
});


$('.J-datepickerTime-range').datePicker({
format: 'YYYY-MM-DD HH:mm',
isRange: true
});


$('.J-datepicker-range').datePicker({
hasShortcut: true,
min: '2018-01-01 06:00:00',
max: '2029-04-29 20:59:59',
isRange: true,
shortcutOptions: [{
name: 'Yesterday',
day: '-1,-1',
time: '00:00:00,23:59:59'
}, {
name: 'Last Week',
day: '-7,0',
time: '00:00:00,'
}, {
name: 'Last Month',
day: '-30,0',
time: '00:00:00,'
}, {
name: 'Last Three Months',
day: '-90, 0',
time: '00:00:00,'
}],
hide: function (type) {
console.info(this.$input.eq(0).val(), this.$input.eq(1).val());
console.info('Type:', type)
}
});
$('.J-datepicker-range-betweenMonth').datePicker({
isRange: true,
between: 'month',
hasShortcut: true,
shortcutOptions: DATAPICKERAPI.rangeMonthShortcutOption1()
});


$('.J-datepicker-range-between30').datePicker({
isRange: true,
between: 30
});

$('.J-yearMonthPicker-single').datePicker({
format: 'YYYY-MM',
min: '2018-01',
max: '2029-04',
hide: function (type) {
console.info(this.$input.eq(0).val());
}
});

$('.J-yearPicker-single').datePicker({
format: 'YYYY',
min: '2018',
max: '2029'
});


});

function sleep(delay) {
	var start = (new Date()).getTime();
	while ((new Date()).getTime() - start < delay) {
		continue;
	}
}


