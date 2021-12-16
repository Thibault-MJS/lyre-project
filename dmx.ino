/* Created by Thibault MINNEBOO */

#include <ESPDMX.h>
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

int valPan = 0;
int valTilt;
int valColor;
int valLum = 68;


const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>DMX Dashboard</title>
    <!-- Style de la page -->
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            background: linear-gradient(
          rgba(0, 0, 0, 0.5), 
          rgba(0, 0, 0, 0.5)
        ), url(https://www.motoconcess.com/nas/commun/annonces/d081d8194eb138ecf15746bf929725899375215e/photo-annonce-suzuki-intruder-m1800r_615873ae98eb9099034506.jpg);
        }

        h1 {
            font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
            color: rgb(255, 255, 255);
            font-size: 4em;
            text-align: center;
            margin-top: 1em;
        }

        .color {
            width: 100px;
            height: 100px;
            border-radius: 10px;
            border: 1px solid #000;
            margin-left: 20px;
        }

        .colors {
            display: flex;
            align-items: center;
            flex-direction: row;
            justify-content: center;
            flex-wrap: wrap;
        }

        .red { background-color: red }
        .white { background-color: white }
        .turquoise { background-color: rgb(4, 139, 154) }
        .cyan { background-color: rgb(43, 250, 250) }
        .vertc { background-color: rgb(70, 243, 107) }
        .magenta { background-color: rgb(255, 0, 179) }
        .bleuc { background-color: rgb(67, 143, 230); }
        .yellow { background-color: yellow; }
        .vert { background-color: green; }
        .rose { background-color: pink; }
        .bleu { background-color: blue; }
        .orange { background-color: orange; }
        .arc { background-image: -webkit-gradient( linear, left top, right top, color-stop(0, #f22), color-stop(0.15, #f2f), color-stop(0.3, #22f), color-stop(0.45, #2ff), color-stop(0.6, #2f2),color-stop(0.75, #2f2), color-stop(0.9, #ff2), color-stop(1, #f22) ); }
        .arc { background-image: gradient( linear, left top, right top, color-stop(0, #f22), color-stop(0.15, #f2f), color-stop(0.3, #22f), color-stop(0.45, #2ff), color-stop(0.6, #2f2),color-stop(0.75, #2f2), color-stop(0.9, #ff2), color-stop(1, #f22) ); }

    </style>
    <script>
        var JoyStick = (function (container, parameters) {
            parameters = parameters || {};
            var title = (undefined === parameters.title ? 'joystick' : parameters.title),
                width = (undefined === parameters.width ? 0 : parameters.width),
                height = (undefined === parameters.height ? 0 : parameters.height),
                internalFillColor = (undefined === parameters.internalFillColor ? '#00AA00' : parameters.internalFillColor),
                internalLineWidth = (undefined === parameters.internalLineWidth ? 2 : parameters.internalLineWidth),
                internalStrokeColor = (undefined === parameters.internalStrokeColor ? '#003300' : parameters.internalStrokeColor),
                externalLineWidth = (undefined === parameters.externalLineWidth ? 2 : parameters.externalLineWidth),
                externalStrokeColor = (undefined === parameters.externalStrokeColor ? '#008000' : parameters.externalStrokeColor),
                autoReturnToCenter = (undefined === parameters.autoReturnToCenter ? true : parameters.autoReturnToCenter);

            // Create Canvas element and add it in the Container object
            var objContainer = document.getElementById(container);
            var canvas = document.createElement('canvas');
            canvas.id = title;
            if (width == 0) width = objContainer.clientWidth;
            if (height == 0) height = objContainer.clientHeight;
            canvas.width = width;
            canvas.height = height;
            objContainer.appendChild(canvas);
            var context = canvas.getContext('2d');

            var pressed = 0; // Bool - 1=Yes - 0=No
            var circumference = 2 * Math.PI;
            var internalRadius = (canvas.width - ((50 * 2) + 10)) / 2;
            var maxMoveStick = internalRadius + 5;
            var externalRadius = internalRadius + 30;
            var centerX = canvas.width / 2;
            var centerY = canvas.height / 2;
            var directionHorizontalLimitPos = canvas.width / 10;
            var directionHorizontalLimitNeg = directionHorizontalLimitPos * -1;
            var directionVerticalLimitPos = canvas.height / 10;
            var directionVerticalLimitNeg = directionVerticalLimitPos * -1;
            // Used to save current position of stick
            var movedX = centerX;
            var movedY = centerY;

            // Check if the device support the touch or not
            if ("ontouchstart" in document.documentElement) {
                canvas.addEventListener('touchstart', onTouchStart, false);
                canvas.addEventListener('touchmove', onTouchMove, false);
                canvas.addEventListener('touchend', onTouchEnd, false);
            }
            else {
                canvas.addEventListener('mousedown', onMouseDown, false);
                canvas.addEventListener('mousemove', onMouseMove, false);
                canvas.addEventListener('mouseup', onMouseUp, false);
            }
            // Draw the object
            drawExternal();
            drawInternal(centerX, centerY);
            /******************************************************
             * Private methods
             *****************************************************/
            /**
             * @desc Draw the external circle used as reference position
             */
            function drawExternal() {
                context.beginPath();
                context.arc(centerX, centerY, externalRadius, 0, circumference, false);
                context.lineWidth = externalLineWidth;
                context.strokeStyle = externalStrokeColor;
                context.stroke();
            }
            /**
             * @desc Draw the internal stick in the current position the user have moved it
             */
            function drawInternal() {
                context.beginPath();
                if (movedX < internalRadius) movedX = maxMoveStick;
                if ((movedX + internalRadius) > canvas.width) movedX = canvas.width - (maxMoveStick);
                if (movedY < internalRadius) movedY = maxMoveStick;
                if ((movedY + internalRadius) > canvas.height) movedY = canvas.height - (maxMoveStick);
                context.arc(movedX, movedY, internalRadius, 0, circumference, false);
                // create radial gradient
                var grd = context.createRadialGradient(centerX, centerY, 5, centerX, centerY, 200);
                // Light color
                grd.addColorStop(0, internalFillColor);
                // Dark color
                grd.addColorStop(1, internalStrokeColor);
                context.fillStyle = grd;
                context.fill();
                context.lineWidth = internalLineWidth;
                context.strokeStyle = internalStrokeColor;
                context.stroke();
            }

            /**
             * @desc Events for manage touch
             */
            function onTouchStart(event) {
                pressed = 1;
            }
            function onTouchMove(event) {
                // Prevent the browser from doing its default thing (scroll, zoom)
                event.preventDefault();
                if (pressed == 1) {
                    movedX = event.touches[0].pageX;
                    movedY = event.touches[0].pageY;
                    // Manage offset
                    movedX -= canvas.offsetLeft;
                    movedY -= canvas.offsetTop;
                    // Delete canvas
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    // Redraw object
                    drawExternal();
                    drawInternal();
                }
            }
            function onTouchEnd(event) {
                pressed = 0;
                // If required reset position store variable
                if (autoReturnToCenter) {
                    movedX = centerX;
                    movedY = centerY;
                }
                // Delete canvas
                context.clearRect(0, 0, canvas.width, canvas.height);
                // Redraw object
                drawExternal();
                drawInternal();
                //canvas.unbind('touchmove');
            }
            /**
             * @desc Events for manage mouse
             */
            function onMouseDown(event) {
                pressed = 1;
            }
            function onMouseMove(event) {
                if (pressed == 1) {
                    movedX = event.pageX;
                    movedY = event.pageY;
                    // Manage offset
                    movedX -= canvas.offsetLeft;
                    movedY -= canvas.offsetTop;
                    // Delete canvas
                    context.clearRect(0, 0, canvas.width, canvas.height);
                    // Redraw object
                    drawExternal();
                    drawInternal();
                }
            }
            function onMouseUp(event) {
                pressed = 0;
                // If required reset position store variable
                if (autoReturnToCenter) {
                    movedX = centerX;
                    movedY = centerY;
                }
                // Delete canvas
                context.clearRect(0, 0, canvas.width, canvas.height);
                // Redraw object
                drawExternal();
                drawInternal();
                //canvas.unbind('mousemove');
            }
            /******************************************************
             * Public methods
             *****************************************************/
            /**
             * @desc The width of canvas
             * @return Number of pixel width 
             */
            this.GetWidth = function () {
                return canvas.width;
            };

            /**
             * @desc The height of canvas
             * @return Number of pixel height
             */
            this.GetHeight = function () {
                return canvas.height;
            };

            /**
             * @desc The X position of the cursor relative to the canvas that contains it and to its dimensions
             * @return Number that indicate relative position
             */
            this.GetPosX = function () {
                return movedX;
            };

            /**
             * @desc The Y position of the cursor relative to the canvas that contains it and to its dimensions
             * @return Number that indicate relative position
             */
            this.GetPosY = function () {
                return movedY;
            };

            /**
             * @desc Normalizzed value of X move of stick
             * @return Integer from -100 to +100
             */
            this.GetX = function () {
                return (100 * ((movedX - centerX) / maxMoveStick)).toFixed();
            };

            /**
             * @desc Normalizzed value of Y move of stick
             * @return Integer from -100 to +100
             */
            this.GetY = function () {
                return ((100 * ((movedY - centerY) / maxMoveStick)) * -1).toFixed();
            };

            /**
             * @desc Get the direction of the cursor as a string that indicates the cardinal points where this is oriented
             * @return String of cardinal point N, NE, E, SE, S, SW, W, NW and C when it is placed in the center
             */
            this.GetDir = function () {
                var result = "";
                var orizontal = movedX - centerX;
                var vertical = movedY - centerY;

                if (vertical >= directionVerticalLimitNeg && vertical <= directionVerticalLimitPos) {
                    result = "C";
                }
                if (vertical < directionVerticalLimitNeg) {
                    result = "N";
                }
                if (vertical > directionVerticalLimitPos) {
                    result = "S";
                }

                if (orizontal < directionHorizontalLimitNeg) {
                    if (result == "C") {
                        result = "W";
                    }
                    else {
                        result += "W";
                    }
                }
                if (orizontal > directionHorizontalLimitPos) {
                    if (result == "C") {
                        result = "E";
                    }
                    else {
                        result += "E";
                    }
                }

                return result;
            };
        });

    </script>
</head>

<body>
    <h1>Dashboard DMX</h1>
    <h1>Déplacements de la lyre</h1>
    <div id="joyDiv" align="center"></div>
    <h1>Luminosité de la lyre</h1>
    <center>
        <input type="range" class="luminosity" min="1" max="68" value="68" style="width: 300px; height: 200px; transform: scale(1.5)" onchange="changeLuminosity()">
    </center>
    <h1>Colors</h1>
    <div class="colors">
        <div align="center" class="color red" onclick="changeLyre(21)"></div>
        <div align="center" class="color white" onclick="changeLyre(5)"></div>
        <div align="center" class="color turquoise" onclick="changeLyre(32)"></div>
        <div align="center" class="color cyan" onclick="changeLyre(10)"></div>
        <div align="center" class="color vertc" onclick="changeLyre(42)"></div>
        <div align="center" class="color magenta" onclick="changeLyre(53)"></div>
        <div align="center" class="color bleuc" onclick="changeLyre(64)"></div>
        <div align="center" class="color yellow" onclick="changeLyre(74)"></div>
        <div align="center" class="color vert" onclick="changeLyre(85)"></div>
        <div align="center" class="color rose" onclick="changeLyre(96)"></div>
        <div align="center" class="color bleu" onclick="changeLyre(106)"></div>
        <div align="center" class="color orange" onclick="changeLyre(117)"></div>
        <div align="center" class="color arc" onclick="changeLyre(160)"></div>
    </div>

    <script>
        var joy = new JoyStick('joyDiv', {

            // The ID of canvas element
            title: 'joystick',

            // width/height
            width: 200,
            height: 200,

            // Internal color of Stick
            internalFillColor: '#eb2f06',

            // Border width of Stick
            internalLineWidth: 5,

            // Border color of Stick
            internalStrokeColor: '#b71540',

            // External reference circonference width
            externalLineWidth: 2,

            //External reference circonference color
            externalStrokeColor: '#e55039',

            // Sets the behavior of the stick
            autoReturnToCenter: false
        });

        var joyInitialPos = {
            x: joy.GetX(),
            y: joy.GetY()
        }

        function changeLyre(color) {
            const xhr = new XMLHttpRequest();

            xhr.onreadystatechange = () => {
                while (xhr.readyState !== 4) return;
            }

            xhr.open('POST', "/changeColor", true);
            xhr.send(`${color}`);
        }

        function changeLuminosity() {
            var inputValue = document.querySelector('input').value;

            const xhr = new XMLHttpRequest();

            xhr.onreadystatechange = () => {
                while (xhr.readyState !== 4) return;
            }

            xhr.open("POST", "/luminosity", true);
            xhr.send(inputValue);
        } 

        setInterval(function () {

            if (joy.GetX() === joyInitialPos.x && joy.GetY() === joyInitialPos.y) return;

            joyInitialPos.x = joy.GetX();
            joyInitialPos.y = joy.GetY();

            const xhr = new XMLHttpRequest();

            xhr.onreadystatechange = () => {
                while (xhr.readyState !== 4) return;
            }
                                                                    
            xhr.open('POST', "/change", true);
            xhr.send(`${joyInitialPos.x};${joyInitialPos.y}`);
        }, 1000)
    </script>
</body>

</html>
)=====";


DMXESPSerial dmx;

ESP8266WebServer serverWeb(80);


void handleRoot() {
  serverWeb.send(200, "text/html", index_html);
}

void handleChange() {
  if (serverWeb.method() != HTTP_POST) {
    return;
  } else {
    Serial.println(serverWeb.arg(0));  
    //int[int] value = serverWeb.arg(0); // moyen de traiter les données
    String value = serverWeb.arg(0);
    int index = value.indexOf(";");
    valPan = map(value.substring(0, index).toInt(), -100, 100, 127, 255);
    valTilt = map(value.substring(index+1, sizeof(value)-1).toInt(), -100, 100, 255, 127);
    
  }
}

void handleColor() {
  if (serverWeb.method() != HTTP_POST) {
    return;
  } else {
    valColor = serverWeb.arg(0).toInt();
    Serial.println(valColor);
  }  
}

void handleLuminosity() {
  if (serverWeb.method() != HTTP_POST) {
    return;
  } else {
    valLum = serverWeb.arg(0).toInt();
    Serial.println(valColor);
  }    
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  WiFi.mode(WIFI_STA);
  char* SSID = "HUAWEI P smart S";
  char* PASSWORD = "tmpc220704";
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println(WiFi.localIP().toString());
  serverWeb.on("/", handleRoot);
  serverWeb.on("/change", handleChange);
  serverWeb.on("/changeColor", handleColor);
  serverWeb.on("/luminosity", handleLuminosity);
  serverWeb.begin();
  dmx.init();
  Serial.println("Connected to DMX");
}

void loop() {
  // put your main code here, to run repeatedly:
 //if (WiFi.isConnected()) {
    serverWeb.handleClient();
    if (valPan) dmx.write(1, valPan);
    if (valTilt) dmx.write(3, valTilt);
    if (valLum) dmx.write(8, valLum);
    if (valColor) dmx.write(6, valColor);
    float cm = analogRead(A0);
    Serial.println(cm);
    dmx.update();
  //}
   // delay(2000);
}
