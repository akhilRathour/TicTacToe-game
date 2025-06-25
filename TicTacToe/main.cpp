#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "texture.h"
#include"grid.h"
#include"renderMove.h"
#include "computerMove.h"

//const int SIZE = 3;
char board[SIZE][SIZE] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};
bool isMove = true; // o's turn



int  main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "TicTacToe", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// Generates Shader object using shaders default.vert and default.frag
	Shader gridShader("default.vert", "default.frag");
	VAO gridVAO;
	VBO gridVBO(0,0);

	setup_grid(gridVAO, gridVBO);

	Shader moveShader("textured.vert", "textured.frag");


	//// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	bool drawTriangle = true;
	float size = 1.0f;
	float color[4] = { 0.8f, 0.3f, 0.02f, 1.0f };

	//// Texture
	Texture texX("O-Jolle_insigna.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture texO("x-png-15.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	texX.texUnit(moveShader, "tex0", 0);
	texO.texUnit(moveShader, "tex0", 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		//drawinf board
		for (int i = 0; i < SIZE; i++) {
						for (int j = 0; j < SIZE; j++)
			{
				if (board[i][j] == 'o')
				{
					draw_cell(i * SIZE + j, true, moveShader, texX, texO); // Draw X
				}
				else if (board[i][j] == 'x')
				{
					draw_cell(i * SIZE + j, false, moveShader, texX, texO); // Draw O
				}
						}
		}
		
		//draw_cell(4, false, moveShader, texX, texO); // Draw X in center
		//draw_cell(8, false, moveShader, texX, texO); // Draw O in top-left
		draw_grid(gridShader, gridVAO);
		
		// user input logic

		if (isMove) {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				// Convert mouse position to NDC
				float xNDC = (xpos / 400.0f) - 1.0f; // Assuming window width is 800
				float yNDC = 1.0f - (ypos / 400.0f); // Assuming window height is 800
				// Determine cell index based on NDC coordinates
				int col = static_cast<int>((xNDC + 1.0f) * SIZE / 2.0f);
				int row = static_cast<int>((1.0f - yNDC) * SIZE / 2.0f);
				if (col >= 0 && col < SIZE && row >= 0 && row < SIZE && board[row][col] == ' ') {
					board[row][col] = isMove ? 'o' : 'x'; // Place X or O
					isMove = !isMove; // Switch turn
				}
			}
		}

		//computer move logic
		
		if (!isMove) {
			computerMove(isMove);
		}


		// ImGUI window creation
		ImGui::Begin("My name is window, ImGUI window");
		// Text that appears in the window
		ImGui::Text("Hello there adventurer!");
		// Checkbox that appears in the window
		ImGui::Checkbox("Draw Triangle", &drawTriangle);
		// Slider that appears in the window
		ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
		// Fancy color editor that appears in the window
		ImGui::ColorEdit4("Color", color);
		// Ends the window
		ImGui::End();


		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	// Delete all the objects we've created
	
	gridShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return -1;
}