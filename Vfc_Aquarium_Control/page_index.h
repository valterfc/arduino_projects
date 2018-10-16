String PROGMEM  printPageIndex() {
  return String("<!DOCTYPE html> \r\n")+
                "<html lang='en'> \r\n"+
                "<head> \r\n"+
                "    <meta charset='UTF-8'> \r\n"+
                "    <meta name='viewport' content='width=device-width, initial-scale=1.0'> \r\n"+
                "    <meta http-equiv='X-UA-Compatible' content='ie=edge'> \r\n"+
                "    <title>ESP8266 Aquarium Control</title> \r\n"+
                "    <style>@import url(https://fonts.googleapis.com/css?family=Exo+2);.gooey,.gooey:after,.gooey:before{border-radius:42% 58% 70% 30%/45% 45% 55% 55%}*{margin:0;padding:0;box-sizing:content-box}body,html{width:100vw;height:100vh;background:#0d0722}body{display:flex;align-items:center;justify-content:center;overflow:hidden;color:#fff;font-family:'Exo 2';font-size:24px;animation:fadeIn .5s reverse}.gooey,.gooey:before{animation:morph 3s linear infinite}.gooey{background-image:linear-gradient(120deg,#34e0f0 0,#b400ff 100%);width:150px;height:144px;transform-style:preserve-3d;outline:transparent solid 1px;will-change:border-radius}.gooey:after,.gooey:before{content:'';width:100%;height:100%;display:block;position:absolute;left:0;top:0;box-shadow:5px 5px 89px rgba(0,102,255,.21);will-change:border-radius,transform,opacity;animation-delay:.2s;background-image:linear-gradient(120deg,rgba(0,67,255,.55) 0,rgba(0,103,255,.89) 100%)}.gooey:before{opacity:.21;animation-duration:1.5s}.gooey:after{animation:morph 3s linear infinite;animation-delay:.4s;opacity:.89;content:'ESP8266 CSS';line-height:120px;text-indent:-21px}@keyframes morph{0%,100%{border-radius:42% 58% 70% 30%/45% 45% 55% 55%;transform:translate3d(0,0,0) rotateZ(.01deg)}34%{border-radius:70% 30% 46% 54%/30% 29% 71% 70%;transform:translate3d(0,5px,0) rotateZ(.01deg)}50%{opacity:.89;transform:translate3d(0,0,0) rotateZ(.01deg)}67%{border-radius:100% 60% 60% 100%/100% 100% 60% 60%;transform:translate3d(0,-3px,0) rotateZ(.01deg)}}@keyframes fadeIn{100%{transform:scale(1.03);opacity:0}}</style> \r\n"
                "</head> \r\n"+
                "<body> \r\n"+
                "    <div class='gooey'></div> \r\n"+
                "</body> \r\n"+
                "</html> \r\n"+
                "\r\n";
}
