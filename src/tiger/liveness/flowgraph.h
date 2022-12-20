#ifndef TIGER_LIVENESS_FLOWGRAPH_H_
#define TIGER_LIVENESS_FLOWGRAPH_H_

#include "tiger/codegen/assem.h"
#include "tiger/frame/frame.h"
#include "tiger/frame/temp.h"
#include "tiger/util/graph.h"

namespace fg {

using FNode = graph::Node<assem::Instr>;
using FNodePtr = graph::Node<assem::Instr>*;
using FNodeListPtr = graph::NodeList<assem::Instr>*;
using FGraph = graph::Graph<assem::Instr>;
using FGraphPtr = graph::Graph<assem::Instr>*;

class FlowGraphFactory {
public:
  explicit FlowGraphFactory(assem::InstrList *instr_list)
      : instr_list_(instr_list), flowgraph_(new FGraph()),
        label_map_(std::make_unique<tab::Table<temp::Label, FNode>>()) {}
  void AssemFlowGraph();
  FGraphPtr GetFlowGraph() { return flowgraph_; }

  [[nodiscard]] static temp::TempList* GetUse(FNodePtr node);
  [[nodiscard]] static temp::TempList* GetDef(FNodePtr node);
  [[nodiscard]] static bool IsMove(FNodePtr node);
  [[nodiscard]] static bool IsCall(FNodePtr node);
  [[nodiscard]] static frame::StringFrag* GetFrag(FNodePtr node);
  [[nodiscard]] static int  GetArgInStack(FNodePtr node);
private:
  assem::InstrList *instr_list_;
  FGraphPtr flowgraph_;
  std::unique_ptr<tab::Table<temp::Label, FNode>> label_map_;
};

} // namespace fg

#endif