# GL Scratch Pad

The GL Scratch Pad is a framework that allows OpenGL programmers to prototype and experiment more easily. It accomplishes this goal by allowing the programmer to designate data as being modifiable by a GUI controller; data modified in such a way is instantly updated and read by the program with no recompilation necessary.

## An example

![A demonstration of GL Scratch Pad](/../master/showcase.gif?raw=true "A demonstration of GL Scratch Pad")

The above shows how GL Scratch Pad works in practice. It's incredibly easy to modify data and the results are instant. It is completely up to the programmer to decide what data is controllable in the interface and how it is used by the application.

### Defining data for the GUI

The GUI is told what data to control in a JSON file. In this example, the JSON is:

```json
{
  "name" : "test",
  "window_width" : 500,
  "window_height" : 500,
  "attributes" : [
	{
		"name" : "diffuse_intensity",
		"type" : "float",
		"value" : 1,
		"min" : 0,
		"max" : 10
	},
	{
		"name" : "specular_intensity",
		"type" : "float",
		"value" : 0.1,
		"min" : 0,
		"max" : 3
	},
	{
		"name" : "ambient_intensity",
		"type" : "float",
		"value" : 0.1,
		"min" : 0,
		"max" : 1
	},
	{
		"name" : "light_pos",
		"type" : "vec3",
		"value" : [0,0,0],
		"min" : [-5,-5,-5],
		"max" : [5,5,5]
	},
	{
		"name" : "t",
		"type" : "transform",
		"value" : {
			"position" : { "value" : [-0.5,0,-2], "min" : [-1,-1,-3], "max" : [1,1,0] },
			"scale" : { "value" : [0.5, 0.5, 0.5] }
		}
	}
  ]
}
```
### Using data

In the OpenGL program, the program can access data like so:

```cpp
GET_F(diffuse_intensity);
```
This line uses the macro `GET_F` to define a float variable `diffuse_intensity` and set its value to the current one as set in the GUI. From there this value can be used a desired. In the example's case it's used to control the intensity of diffuse shading. 

## State of the framework

In its current state, GL Scratch Pad is already completely usable for its purpose. There are still, however, areas to add and improve, such as:
- Camera controls
- Support for more data types
- Adding new OpenGL programs requires recompilation of the framework. At some point it would be nice to use a plugin architecture instead.
- Support for defining image effects and allowing them to be activated for any running OpenGL program

## Installation and Usage

The framework depends on Qt 5.7, and is only tested on Windows. 

I still need to write a comprehensive readme, so in the meantime if you would like to use GL Scratch Pad, please e-mail me at ryankitner@gmail.com and I will help you out.
