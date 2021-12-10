$(document).ready(function() {
	check_session();
	get_file();
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

// 对json串进行检索
function search_json(json) {
	var filename = document.getElementById("search_filename").value;
	
	for(var i = 0; i<json.length; i++)
	{
		if(json[i].name.indexOf(filename) != -1)
		{
			add_file(json[i].name);
		}
	   //alert(json[i].name);
	}
}

// 搜索
function search_file() {
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
			if(jsonstr.length != 0)
			{
				var json = JSON.parse(jsonstr);
				//alert(json["A"]);
				//alert("调用get_json,传参json对象");
				search_json(json);
			}
			//alert("json:"+jsonstr);
			// 将jsonstr转换为json对象 json
		}
	}
	xmlhttp.open("GET","cgi-bin/get_log_file.cgi?get",true);
	xmlhttp.send();
}

// 下载
function download_file(filename) {
	var $form = $('<form method="GET"><a id="downFile"></a></form>');
	$form.appendTo($('body'));
	var str = "../log/" + filename;
	$("#downFile").attr('href',str);
	$("#downFile").attr('download',filename);
	$("#downFile")[0].click();
}

// 添加一个tr,ajax获取
function add_file(s1) {
	//创建一个tr  
	var tr = document.createElement("tr");  
	//其中获取的listbody是要将表格添加的位置的id  
	var listbody = document.getElementById("listbody"); 
    //创建td  
	var td1 = document.createElement("td"); 	
	var td2 = document.createElement("td"); 
	var td3 = document.createElement("td"); 
	
	//alert("相关信息正确");
	var filename = document.createElement("span");
	filename.innerHTML = s1;
	td1.appendChild(filename); 
	
	var download = document.createElement("img");
	download.src = "img/download.png";
	download.onclick = function(){
		download_file(s1);
	}
	td2.appendChild(download); 
	td2.style.width = "100px";
	
	var delete_file = document.createElement("img");
	delete_file.src = "img/delete.png";
	delete_file.onclick = function(){
		if(confirm('确认删除吗？')){
			del_log_file(s1);
			listbody.removeChild(tr);
		}
	}
	td3.appendChild(delete_file); 
	td3.style.width = "100px";
	
	tr.appendChild(td1);  
	tr.appendChild(td2);  
	tr.appendChild(td3);    
	//使用appendChild（tr）方法，将tr添加到listbody中  
	listbody.appendChild(tr); 
}

// 解析json对象
function get_json(json) {
    //alert("进入get_json函数");
    
	for(var i = 0; i<json.length; i++){
        add_file(json[i].name);
       //alert(json[i].name);
    }
    //alert("get_json运行完毕");
};

// 获取云端文件信息
function get_file()
{
	//$('.table1 tbody').html('');
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
			if(jsonstr.length != 0)
			{
				var json = JSON.parse(jsonstr);
				//alert(json["A"]);
				//alert("调用get_json,传参json对象");
				get_json(json);
			}
			//alert("json:"+jsonstr);
			// 将jsonstr转换为json对象 json
		}
	}
	xmlhttp.open("GET","cgi-bin/get_log_file.cgi?get",true);
	xmlhttp.send();
};

// 删除当前行，同步到本地文件
function del_log_file(s1) {
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
			if(ret.length != 0)
			{
				alert(ret);
			}
			//alert(str);
		}
	}
	xmlhttp.open("GET","cgi-bin/del_log_file.cgi?del_file:" +s1+ "|",true);
	xmlhttp.send();
}
