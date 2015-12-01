(* Content-type: application/vnd.wolfram.cdf.text *)

(*** Wolfram CDF File ***)
(* http://www.wolfram.com/cdf *)

(* CreatedBy='Mathematica 10.0' *)

(*************************************************************************)
(*                                                                       *)
(*  The Mathematica License under which this file was created prohibits  *)
(*  restricting third parties in receipt of this file from republishing  *)
(*  or redistributing it by any means, including but not limited to      *)
(*  rights management or terms of use, without the express consent of    *)
(*  Wolfram Research, Inc. For additional information concerning CDF     *)
(*  licensing and redistribution see:                                    *)
(*                                                                       *)
(*        www.wolfram.com/cdf/adopting-cdf/licensing-options.html        *)
(*                                                                       *)
(*************************************************************************)

(*CacheID: 234*)
(* Internal cache information:
NotebookFileLineBreakTest
NotebookFileLineBreakTest
NotebookDataPosition[      1064,         20]
NotebookDataLength[      6296,        215]
NotebookOptionsPosition[      6638,        203]
NotebookOutlinePosition[      6974,        218]
CellTagsIndexPosition[      6931,        215]
WindowFrame->Normal*)

(* Beginning of Notebook Content *)
Notebook[{

Cell[CellGroupData[{
Cell[BoxData[
 RowBox[{"solution", "=", 
  RowBox[{"DSolve", "[", 
   RowBox[{
    RowBox[{"{", 
     RowBox[{
      RowBox[{
       RowBox[{
        RowBox[{"y", "''"}], "[", "x", "]"}], "\[Equal]", 
       RowBox[{"y", "[", "x", "]"}]}], ",", 
      RowBox[{
       RowBox[{
        RowBox[{"y", "'"}], "[", "0", "]"}], "\[Equal]", "0"}]}], "}"}], ",", 
    
    RowBox[{"y", "[", "x", "]"}], ",", "x"}], "]"}]}]], "Input",
 CellChangeTimes->{{3.645343972566341*^9, 3.645343976131254*^9}}],

Cell[BoxData[
 RowBox[{"{", 
  RowBox[{"{", 
   RowBox[{
    RowBox[{"y", "[", "x", "]"}], "\[Rule]", 
    RowBox[{
     SuperscriptBox["\[ExponentialE]", 
      RowBox[{"-", "x"}]], " ", 
     RowBox[{"(", 
      RowBox[{"1", "+", 
       SuperscriptBox["\[ExponentialE]", 
        RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
     RowBox[{"C", "[", "1", "]"}]}]}], "}"}], "}"}]], "Output",
 CellChangeTimes->{3.6453443727272997`*^9, 3.645344453122932*^9, 
  3.64534459289189*^9}]
}, Open  ]],

Cell[CellGroupData[{

Cell[BoxData[
 RowBox[{
  RowBox[{"g", "[", "x_", "]"}], "=", 
  RowBox[{
   RowBox[{"y", "[", "x", "]"}], "/.", 
   RowBox[{"solution", "[", 
    RowBox[{"[", "1", "]"}], "]"}]}]}]], "Input",
 CellChangeTimes->{{3.6453440824281073`*^9, 3.645344082430663*^9}}],

Cell[BoxData[
 RowBox[{
  SuperscriptBox["\[ExponentialE]", 
   RowBox[{"-", "x"}]], " ", 
  RowBox[{"(", 
   RowBox[{"1", "+", 
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
  RowBox[{"C", "[", "1", "]"}]}]], "Output",
 CellChangeTimes->{3.64534437295894*^9, 3.645344453423986*^9, 
  3.6453445932118387`*^9}]
}, Open  ]],

Cell[CellGroupData[{

Cell[BoxData[
 RowBox[{
  RowBox[{"t", "[", "x_", "]"}], "=", 
  RowBox[{"Table", "[", 
   RowBox[{
    RowBox[{
     RowBox[{"g", "[", "x", "]"}], "/.", 
     RowBox[{
      RowBox[{"C", "[", "2", "]"}], "\[Rule]", "j"}]}], ",", 
    RowBox[{"{", 
     RowBox[{"j", ",", "1", ",", "10"}], "}"}]}], "]"}]}]], "Input",
 CellChangeTimes->{{3.645344099998925*^9, 3.645344100002384*^9}}],

Cell[BoxData[
 RowBox[{"{", 
  RowBox[{
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}], ",", 
   RowBox[{
    SuperscriptBox["\[ExponentialE]", 
     RowBox[{"-", "x"}]], " ", 
    RowBox[{"(", 
     RowBox[{"1", "+", 
      SuperscriptBox["\[ExponentialE]", 
       RowBox[{"2", " ", "x"}]]}], ")"}], " ", 
    RowBox[{"C", "[", "1", "]"}]}]}], "}"}]], "Output",
 CellChangeTimes->{3.645344373156827*^9, 3.6453444534806643`*^9, 
  3.6453445932719297`*^9}]
}, Open  ]],

Cell[BoxData[
 RowBox[{"Export", "[", 
  RowBox[{"\"\</home/pi/dinneuro/input.csv\>\"", ",", 
   RowBox[{"t", "[", "x_", "]"}], ",", " ", "\"\<CSV\>\""}], "]"}]], "Input",
 CellChangeTimes->{{3.645344314836269*^9, 3.645344362130804*^9}, {
  3.6453444400544024`*^9, 3.645344444155526*^9}, {3.645344582378345*^9, 
  3.6453445896042643`*^9}, {3.645344668155511*^9, 3.645344693586012*^9}}]
},
WindowSize->{1700, 832},
WindowMargins->{{0, Automatic}, {Automatic, 0}},
FrontEndVersion->"10.0 for Linux ARM (32-bit) (February 3, 2015)",
StyleDefinitions->"Default.nb"
]
(* End of Notebook Content *)

(* Internal cache information *)
(*CellTagsOutline
CellTagsIndex->{}
*)
(*CellTagsIndex
CellTagsIndex->{}
*)
(*NotebookFileOutline
Notebook[{
Cell[CellGroupData[{
Cell[1486, 35, 491, 15, 30, "Input"],
Cell[1980, 52, 477, 14, 34, "Output"]
}, Open  ]],
Cell[CellGroupData[{
Cell[2494, 71, 260, 7, 32, "Input"],
Cell[2757, 80, 348, 10, 34, "Output"]
}, Open  ]],
Cell[CellGroupData[{
Cell[3142, 95, 383, 11, 32, "Input"],
Cell[3528, 108, 2706, 84, 34, "Output"]
}, Open  ]],
Cell[6249, 195, 385, 6, 32, "Input"]
}
]
*)

(* End of internal cache information *)

(* NotebookSignature JuTT5COg#ITxRBg@E91XcJaa *)
