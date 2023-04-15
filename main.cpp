#include <wx/sizer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <vector>
#include "app/app_state.hpp"
#include "algorithms/DFS.hpp"

class BasicDrawPane : public wxPanel
{

public:
  BasicDrawPane(wxFrame* parent);

  void paintEvent(wxPaintEvent& evt);
  void paintNow();
  void render(wxDC& dc);

  DECLARE_EVENT_TABLE()
};

class MyFrame;

class MyApp : public wxApp
{
  bool renderLoopOn;
  bool OnInit();
  void onIdle(wxIdleEvent& evt);

  MyFrame* frame;
  BasicDrawPane* drawPane;
public:
  void activateRenderLoop(bool on);

};


IMPLEMENT_APP_NO_MAIN(MyApp)
int main() {
  algo::AppState::getInstance()->changeAlgo<algo::BFS_ALL_NODES>();
  wxEntry();
}


class MyFrame : public wxFrame
{
public:
  MyFrame() : wxFrame((wxFrame*)NULL, -1, wxT("Algorithm Visualization"), wxPoint(50, 50), wxSize(meta::width + meta::pixel_alloc, meta::height+ meta::formatting_factor))
  {}
  void onClose(wxCloseEvent& evt)
  {
    wxGetApp().activateRenderLoop(false);
    evt.Skip(); // don't stop event, we still want window to close
  }
  DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_CLOSE(MyFrame::onClose)
END_EVENT_TABLE()

bool MyApp::OnInit()
{
  renderLoopOn = false;
  algo::AppState* inst = algo::AppState::getInstance();
  for (int i = 0; i < meta::node_row_count; i++) {
    for (int j = 0; j < meta::node_row_count; j++) {
      if (i*meta::node_row_count + j == meta::genesis_point) {
        Node* node = new Node{ kNodeType::Genesis, {i * (meta::pixel_alloc + meta::gap), j * (meta::pixel_alloc + meta::gap) + meta::text_padding} };
        inst->nodes.push_back(node);
        inst->init(meta::genesis_point);
      }
      else if (i * meta::node_row_count + j == meta::dest && inst->algoHasDestination()) {
        Node* node = new Node{ kNodeType::Destination, {i * (meta::pixel_alloc + meta::gap), j * (meta::pixel_alloc + meta::gap) + meta::text_padding} };
        inst->nodes.push_back(node);
      }
      else
        inst->nodes.push_back(new Node{ kNodeType::Unmarked, {i * (meta::pixel_alloc + meta::gap), j * (meta::pixel_alloc + meta::gap) + meta::text_padding} });
    }
  }

  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new MyFrame();

  drawPane = new BasicDrawPane(frame);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->Show();

  activateRenderLoop(true);
  return true;
}

void MyApp::activateRenderLoop(bool on)
{
  if (on && !renderLoopOn)
  { 
    Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));
    renderLoopOn = true;
  }
  else if (!on && renderLoopOn)
  {
    Disconnect(wxEVT_IDLE, wxIdleEventHandler(MyApp::onIdle));
    renderLoopOn = false;
  }
}
void MyApp::onIdle(wxIdleEvent& evt)
{
  if (renderLoopOn)
  {
    drawPane->paintNow();
    evt.RequestMore(); // render continuously, not only once on idle
  }
}


BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
EVT_PAINT(BasicDrawPane::paintEvent)
END_EVENT_TABLE()



BasicDrawPane::BasicDrawPane(wxFrame* parent) :
  wxPanel(parent)
{
}


void BasicDrawPane::paintEvent(wxPaintEvent& evt)
{
  wxPaintDC dc(this);
  render(dc);
}

void BasicDrawPane::paintNow()
{
  wxClientDC dc(this);
  render(dc);
}
void BasicDrawPane::render(wxDC& dc)
{
  algo::AppState* inst = algo::AppState::getInstance();
  dc.DrawText(inst->getAlgoName(), 280, 10);
  dc.SetBackground(wxColour(100, 100, 100));
  if (++inst->time % inst->speed_factor == 0 && !inst->algoIsDone()) {
    inst->appNext();
  }
    for (int i = 0; i < inst->nodes.size(); i++) {
      wxColour a;
      switch (inst->nodes[i]->type) {
      case kNodeType::Genesis: {
        a = wxColour(0, 255, 0);
      } break;
      case kNodeType::Unmarked: {
        a = wxColour(20, 20, 20);
      } break;
      case kNodeType::Marked: {
        a = wxColour(255, 0, 0);
      } break;
      case kNodeType::Seen: {
        a = wxColour(255, 255, 0);
      } break;
      case kNodeType::Destination: {
        a = wxColour(255, 0, 255);
      } break;
      }
      dc.SetPen(wxPen(a, 2));
      dc.GradientFillLinear({ inst->nodes[i]->pos.x, inst->nodes[i]->pos.y, meta::pixel_alloc, meta::pixel_alloc }, a, a);
      //dc.DrawRectangle(nodes[i]->pos.x, nodes[i]->pos.y, pixel_alloc, pixel_alloc);
   }
  //dc.DrawText(wxT("Testing"), 40, y);
}