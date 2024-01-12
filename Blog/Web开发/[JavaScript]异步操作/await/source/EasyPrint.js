
//新增print函数以向HTML中写入字串
//顺手修改标题名

let path = decodeURI(location.href);
let lst = path.split('/');
let fileName = lst[lst.length - 1];
let name = fileName.split('.')[0];//文件名，作为标题

let op = document.createElement("p");
let print = (str) => {
	str = str == undefined ? "" : str
	op.innerHTML += '<font color=#00FFFF>></font> $str<br>'.replace("$str", str);
}

document.body.append(op);
document.title = name;

op.innerHTML = '【$name】<br><br>'.replace('$name', name);
op.style = "font-size:20px"


