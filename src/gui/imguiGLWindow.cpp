// Copyright (c) 2021 Farzon Lotfi All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "imguiGLWindow.h"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "runtime/binaryDisassemble.h"
#include <ImGuiFileDialog/ImGuiFileDialog.h>
#include "splitstring.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

void GozihrWindow::Draw() {
  ImGui::Begin("Gozihr", &gozihr_active, ImGuiWindowFlags_MenuBar);
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open..", "Ctrl+O")) {
        std::string typeFilters = ".exe,.dll,.lib,.out,.a,.so,.dylib,.*";
        std::string startPath = ".";
        ImGuiFileDialog::Instance()->OpenDialog(
            "ChooseFileDlgKey", "Choose File", typeFilters.c_str(), startPath);
      }
      if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
      }
      if (ImGui::MenuItem("Close", "Ctrl+W")) {
        gozihr_active = false;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
  // display
  if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
    // action if OK
    if (ImGuiFileDialog::Instance()->IsOk()) {
      filePath = ImGuiFileDialog::Instance()->GetFilePathName();
    }

    // close
    ImGuiFileDialog::Instance()->Close();
  }
  ImGui::InputText("binary path: ", const_cast<char *>(filePath.c_str()),
                   filePath.capacity() + 1);
  if (ImGui::Button("Disassemble")) {
    Disassemble(filePath);
  }
  // Display contents in a scrolling region
  if (ImGui::BeginChild("Test Region"))
  {
  size_t q = 1;
  const char* dstring = disasm.c_str();
  size_t dlen = disasm.length();
  std::string dlim = "\n";

  if (ImGui::BeginChild("Scrolling")){
  
  ImGui::Text("Working Area 1");
  ImGui::Separator();
  
  /* C++ substrings */
  /*
  std::string workingcopy = disasm;
  std::string d1 = "\n";
  std::string d2 = "|";
  size_t pos1 = 0;
  size_t pos2 = 0;

  std::string tok1;
  std::string tok2;
  bool found2=false;
  
  while ((pos1 = workingcopy.find(d1)) != std::string::npos) {
    tok1 = workingcopy.substr(0, pos1);
    std::string backup = tok1;
    while ((pos2 = tok1.find(d2))!= std::string::npos){
      found2 = true;
      tok2 = tok1.substr(0, pos2);
      ImGui::Text("%s", tok2);
      tok1.erase(0, pos2 + d2.length());    
    }
    if (found2) {
      ImGui::Text("%s", tok2);
    }
    // add last thing to figure
    workingcopy.erase(0, pos1 + d1.length());
  }
  */ 


  /* as a cstring */
  
  
  char * teststr;
  
  
  teststr = new char[dlen + 1]();
  strncpy(teststr, dstring, dlen + 1);
  char * splitres = strtok(teststr, dlim.c_str());
  while (splitres != NULL){
    //ImGui::Text("%s", splitres);
    splitres = strtok(NULL, dlim.c_str());
    q++; // get max size of value vec
  }
  if(q>5){
  ImGui::Text("Read Output");}
  ImGui::Separator();
  if (ImGui::BeginChild("Second Area")){
    ImGui::Text("Working Area 2");
  if (q>5)
  {
    char * valvec[q];
    char * t2str;
    char * target;
    //char * thing = "address";
    size_t r = 0;
    t2str = new char[dlen + 1]();
    strncpy(t2str, dstring, dlen + 1); // reload teststr
    char * newres = strtok(t2str, dlim.c_str());
    valvec[r] = newres;
    r++;
    while (newres != NULL){
      //ImGui::Text("%s", splitres);
      newres = strtok(NULL, dlim.c_str());
      valvec[r] = newres;
      r++; // get max size of value vec
    }
    //ImGui::Text("%s", valvec[5]);// 5 is the header row
    char * headers[3];
    size_t hndx = 0;
    std::string hdlim = "|";
    char * h3str = new char[strlen(valvec[5]) + 1]();
    strncpy(h3str, valvec[5], strlen(valvec[5]) + 1);
    char * hval = strtok(h3str, hdlim.c_str());
    headers[hndx] = hval;
    hndx++;
    while (hval != NULL && hndx<4){
      hval = strtok(NULL, hdlim.c_str());
      headers[hndx] = hval;
      hndx++;
    }
    for (int i = 0; i < 3; i++)
    {
      ImGui::Text("%s", headers[i]);
    }
    ImGui::Separator();
    static bool selected[3] = {};
    if (ImGui::BeginTable("DisasmData",3))
    {
      ImGui::TableNextColumn(); 
      for (int i = 0; i < 3; i++)
                {
                    char label[strlen(headers[i]+1)];
                    sprintf(label, "%s", headers[i]);
                    ImGui::Selectable(label, &selected[i]);
                    ImGui::TableNextColumn(); 
                }
                ImGui::EndTable();
    }
    ImGui::Separator();



  }
  
  }
  ImGui::EndChild();
  }
  ImGui::EndChild();
  
  /*
  }
  */
  
  
  //ImGui::Text("..\n");
  /* Attempt at using getline */
  //std::vector<std::string> strs;
  //std::istringstream f(disasm);
  //std::string s;
  //while (std::getline(f, s, '\n')){
  //std::istringstream g(s);
  //std::string p;
  //while (std::getline(g, p, '|')){
  //  if (!p.empty()){ImGui::Text("%s",p);}
  //}
  /* Basic tests and text formatting */
    //const char* currthing = s.c_str();
    //int currlen = strlen(currthing);
    //char* innerstr;
    //innerstr = new char[currlen + 1]();
    //strncpy(innerstr, currthing, currlen+1);    
    //splitstring q(innerstr);
    //std::vector<std::string> headers = q.split('|',0);
    //for (int k = 0; k < headers.size(); k++){
    //  ImGui::Text("%s", headers[k]);
    //}
    //strs.push_back(s);
  //}
  //ImGui::Text("..\n");
  //ImGui::Text("%d", strlen(disasm.c_str()));
  //ImGui::Text("%d", disasm.length());
  //ImGui::Text("%s", disasm.c_str());
  
  }
  ImGui::EndChild();
  ImGui::End();
}

void GozihrWindow::Disassemble(std::string binaryPath, std::string pluginPath) {
  if (binaryPath.empty()) {
    // TODO ImGui::OpenPopup
    return;
  }
  std::stringstream stream;
  BinaryDisassemble::action(binaryPath, pluginPath, stream);
  disasm = stream.str();
}

ImguiGLWindow::ImguiGLWindow(std::string title, int width, int height)
    : GLWindow(title, width, height) {
  mGozihrWindow = std::make_unique<GozihrWindow>();
}

void ImguiGLWindow::init() {
  GLWindow::init();
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(this->getGLFWwindow(), true);
  ImGui_ImplOpenGL3_Init(GLWindow::glslVersion);
  drawFunctors.push_back([this]() { this->mGozihrWindow->Draw(); });
}

void ImguiGLWindow::draw() {
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  for (const std::function<void()> &df : drawFunctors) {
    df();
  }

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(this->getGLFWwindow(), &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
