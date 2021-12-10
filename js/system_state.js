$(document).ready(function() {
	check_session();
	get_private_ip();
	get_states();
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

// 获取私网IP
function get_private_ip()
{
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
		if(xmlhttp.readyState==4)
		{
			if(xmlhttp.status==200)
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
					
				}
				else
				{
					if(ret.indexOf("error") != -1)
					{
						alert(ret);
					}
					else
					{
						$("#private_ip").html(ret);
					}
				}
			}
			else
			{
				//alert(xmlhttp.status);
			}

		}
		else
		{
			//alert(xmlhttp.readyState);
		}
	}
	xmlhttp.open("GET","cgi-bin/get_private_ip.cgi?get",true);
	xmlhttp.send();
}

// 获取CPU、内存、硬盘占用情况
function get_states()
{
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
		if(xmlhttp.readyState==4)
		{
			if(xmlhttp.status==200)
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
					set_cpu(json["cpu"]);
					set_memory(json["memory"]);
					set_disk(json["disk"]);
				}
			}
			else
			{
				//alert(xmlhttp.status);
			}

		}
		else
		{
			//alert(xmlhttp.readyState);
		}
	}
	xmlhttp.open("GET","cgi-bin/get_states.cgi?get_states",true);
	xmlhttp.send();
}

// 设置扇形图
function set_cpu(str)
{
	var str1 = parseInt(str);
	var str2 = 100 - str1; 
	
	var dom = document.getElementById("container_cpu");
	var myChart = echarts.init(dom);
	var app = {};
	option = null;
	option = {
	    backgroundColor: '#2c343c',
	
	    title: {
	        text: 'CPU',
	        left: 'center',
	        top: 20,
	        textStyle: {
	            color: '#ccc'
	        }
	    },
	
	    tooltip : {
	        trigger: 'item',
	        formatter: "{a} <br/>{b} : {c} ({d}%)"
	    },
	
	    visualMap: {
	        show: false,
	        min: 20,
	        max: 100,
	        inRange: {
	            colorLightness: [0, 1]
	        }
	    },
	    series : [
	        {
	            name:'占比',
	            type:'pie',
	            radius : '60%',
	            center: ['50%', '50%'],
	            data:[
	                {value:str1, name:'已用'},
	                {value:str2, name:'剩余'}
	            ].sort(function (a, b) { return a.value - b.value; }),
	            roseType: 'radius',
	            label: {
	                normal: {
	                    textStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    }
	                }
	            },
	            labelLine: {
	                normal: {
	                    lineStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    },
	                    smooth: 0.2,
	                    length: 10,
	                    length2: 20
	                }
	            },
	            itemStyle: {
	                normal: {
	                    color: '#c23531',
	                    shadowBlur: 200,
	                    shadowColor: '#2c343c'
	                }
	            },
	
	            animationType: 'scale',
	            animationEasing: 'elasticOut',
	            animationDelay: function (idx) {
	                return Math.random() * 200;
	            }
	        }
	    ]
	};;
	if (option && typeof option === "object") {
	    myChart.setOption(option, true);
	}
}

function set_memory(str)
{
	var str1 = parseInt(str);
	var str2 = 100 - str1; 
	
	var dom = document.getElementById("container_memory");
	var myChart = echarts.init(dom);
	var app = {};
	option = null;
	option = {
	    backgroundColor: '#2c343c',
	
	    title: {
	        text: '内存',
	        left: 'center',
	        top: 20,
	        textStyle: {
	            color: '#ccc'
	        }
	    },
	
	    tooltip : {
	        trigger: 'item',
	        formatter: "{a} <br/>{b} : {c} ({d}%)"
	    },
	
	    visualMap: {
	        show: false,
	        min: 20,
	        max: 100,
	        inRange: {
	            colorLightness: [0, 1]
	        }
	    },
	    series : [
	        {
	            name:'占比',
	            type:'pie',
	            radius : '60%',
	            center: ['50%', '50%'],
	            data:[
	                {value:str1, name:'已用'},
	                {value:str2, name:'剩余'}
	            ].sort(function (a, b) { return a.value - b.value; }),
	            roseType: 'radius',
	            label: {
	                normal: {
	                    textStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    }
	                }
	            },
	            labelLine: {
	                normal: {
	                    lineStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    },
	                    smooth: 0.2,
	                    length: 10,
	                    length2: 20
	                }
	            },
	            itemStyle: {
	                normal: {
	                    color: '#c23531',
	                    shadowBlur: 200,
	                    shadowColor: '#2c343c'
	                }
	            },
	
	            animationType: 'scale',
	            animationEasing: 'elasticOut',
	            animationDelay: function (idx) {
	                return Math.random() * 200;
	            }
	        }
	    ]
	};;
	if (option && typeof option === "object") {
	    myChart.setOption(option, true);
	}
}


function set_disk(str)
{
	var str1 = parseInt(str);
	var str2 = 100 - str1; 
	
	var dom = document.getElementById("container_disk");
	var myChart = echarts.init(dom);
	var app = {};
	option = null;
	option = {
	    backgroundColor: '#2c343c',
	
	    title: {
	        text: '硬盘',
	        left: 'center',
	        top: 20,
	        textStyle: {
	            color: '#ccc'
	        }
	    },
	
	    tooltip : {
	        trigger: 'item',
	        formatter: "{a} <br/>{b} : {c} ({d}%)"
	    },
	
	    visualMap: {
	        show: false,
	        min: 20,
	        max: 100,
	        inRange: {
	            colorLightness: [0, 1]
	        }
	    },
	    series : [
	        {
	            name:'占比',
	            type:'pie',
	            radius : '60%',
	            center: ['50%', '50%'],
	            data:[
	                {value:str1, name:'已用'},
	                {value:str2, name:'剩余'}
	            ].sort(function (a, b) { return a.value - b.value; }),
	            roseType: 'radius',
	            label: {
	                normal: {
	                    textStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    }
	                }
	            },
	            labelLine: {
	                normal: {
	                    lineStyle: {
	                        color: 'rgba(255, 255, 255, 0.3)'
	                    },
	                    smooth: 0.2,
	                    length: 10,
	                    length2: 20
	                }
	            },
	            itemStyle: {
	                normal: {
	                    color: '#c23531',
	                    shadowBlur: 200,
	                    shadowColor: '#2c343c'
	                }
	            },
	
	            animationType: 'scale',
	            animationEasing: 'elasticOut',
	            animationDelay: function (idx) {
	                return Math.random() * 200;
	            }
	        }
	    ]
	};;
	if (option && typeof option === "object") {
	    myChart.setOption(option, true);
	}
}
