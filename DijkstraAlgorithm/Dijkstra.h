#pragma once
#define INFINITE 99999999
namespace DijkstraAlgorithm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Dijkstra
	/// </summary>
	public ref class Dijkstra : public System::Windows::Forms::Form
	{
	//clr related stuff
	public: 
		int w;
		int h;
		Graphics ^g;
		Pen ^blackPen;
		System::Drawing::Font^ drawFont;
		SolidBrush^ drawBrush;
		array<int, 2>^ points = gcnew array<int, 2>(10, 2);



	//actual variables used in program
	public:
		int n;
		array<int, 2>^ adj = gcnew array<int, 2>(10, 10);
		array<int>^ visited = gcnew array<int>(10);
		array<int>^ distance = gcnew array<int>(10);
		array<int>^ path = gcnew array<int>(10);
		int sourceNode;
		int destNode;
		int pathIndex = 0;
		int currNode;
	//variable involved in finding the shortest route
		int index;
		//array<int>^ route = gcnew array<int>(10);
		//int k;
		int i;
		int j;


	private: System::Windows::Forms::Label^  label5;
	public:
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
			 


	public:
		Dijkstra(void)
		{
			InitializeComponent();
			
			createImage();

			hardcodePoints();

			resettingPens();

			resetFont();

			//drawNodes();
			//
			//TODO: Add the constructor code here
			//
		}

		void createImage()
		{
			//getting height and width of the picture box
			w = pictureBox1->Width;
			h = pictureBox1->Height;
			//creating new image
			pictureBox1->Image = gcnew Bitmap(w, h);
			//pointer to image
			g = Graphics::FromImage(pictureBox1->Image);
		}

		void resettingPens()
		{
			//setting pen for drawing
			blackPen = gcnew Pen(Color::Black);
		}

		void resetFont()
		{
			//setting font and brush
			drawFont = gcnew System::Drawing::Font("Arial", 16);
			drawBrush = gcnew SolidBrush(Color::Black);
		}

		void setLabellingFont()
		{
			//changing font for labelling weights of the edges
			drawFont = gcnew System::Drawing::Font("Arial", 10);
			drawBrush = gcnew SolidBrush(Color::Blue);
		}

		void setMarkingPen()
		{
			//changing pen color for marking the shortest route
			blackPen = gcnew Pen(Color::Pink);
		}

		void hardcodePoints()
		{
			// hardcoding the coordinates of the points of the nodes
			points[0, 0] = 350;
			points[0, 1] = 50;

			points[1, 0] = 200;
			points[1, 1] = 100;

			points[2, 0] = 50;
			points[2, 1] = 150;

			points[3, 0] = 50;
			points[3, 1] = 200;

			points[4, 0] = 200;
			points[4, 1] = 250;

			points[5, 0] = 350;
			points[5, 1] = 300;

			points[6, 0] = 500;
			points[6, 1] = 250;

			points[7, 0] = 650;
			points[7, 1] = 200;

			points[8, 0] = 650;
			points[8, 1] = 150;

			points[9, 0] = 500;
			points[9, 1] = 100;
		}

		void drawNodes()
		{
			//drawing nodes and labeling them
			for (int i = 0; i < n; i++)
			{
				g->DrawEllipse(blackPen, points[i, 0], points[i, 1], 15, 15);
				g->DrawString(i.ToString(), drawFont, drawBrush, PointF(points[i, 0] - 20, points[i, 1] - 17));
			}
		}

		void clrAdjacency()
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					adj[i, j] = 0;
				}
			}
		}

		void infDist()
		{
			//initializing all the distances to infinite
			for (int i = 0; i < n; i++)
			{
				distance[i] = INFINITE;
			}
		}

		void drawEdge(int a, int b, int x)
		{
			setLabellingFont();
			adj[a, b] = x;
			adj[b, a] = x;
			g->DrawLine(blackPen, points[a, 0] + 7, points[a, 1] + 7, points[b, 0] + 7, points[b, 1] + 7);
			g->DrawString(x.ToString(), drawFont, drawBrush, PointF((points[a, 0] + points[b, 0] - 10) / 2, (points[a, 1] + points[b, 1] - 10) / 2));
			resetFont();
		}

		void markEdge(int a, int b)
		{
			g->DrawLine(blackPen, points[a, 0] + 7, points[a, 1] + 7, points[b, 0] + 7, points[b, 1] + 7);
		}


		void calcShortestDist()
		{
			infDist();
			//marking the source node as visited, it's distance to  and adding to the path
			visited[sourceNode] = 1;
			path[pathIndex++] = sourceNode;
			distance[sourceNode] = 0;

			//setting the currNode to sourceNode
			currNode = sourceNode;

			//finding the shortest path to the destination
			for (int i = 0; i < n; i++)
			{
				if (currNode == destNode) // already reached the destination
					break;
				int smallest = INFINITE, smallestIndex;
				int allVisited = 0;
				for (int j = 0; j < n; j++)
				{
					if (visited[j] == 1) //node already visited will be skipped
					{
						allVisited++;
						continue;
					}
					if (j == currNode) //if on the same node then skip
						continue;
					if (adj[currNode,j] != 0) //nodes are adjacent to eachother
					{
						if (distance[j] > (distance[currNode] + adj[currNode, j])) // if shorter distance available then put it
							distance[j] = distance[currNode] + adj[currNode, j];
					}
					if (smallest > distance[j]) // for getting node with smallest distance
					{
						smallest = distance[j];
						smallestIndex = j;
					}
				}

				if (allVisited == n) //if already visited all nodes then stop the operation 
					break;

				path[pathIndex++] = smallestIndex;
				visited[smallestIndex] = 1;
				currNode = smallestIndex;
			}

			//initializing values for route
			index = 0;
			//k = 0;
			i = pathIndex - 1;
			j = pathIndex - 2;

			//finding the shortest route
			setMarkingPen();
			while (i >= 0)
			{
				if (i == 0)
				{
					//route[k++] = path[i];
					break;
				}
				if (adj[path[i], path[j]] == (distance[path[i]] - distance[path[j]]) && adj[path[i], path[j]] != 0) //verifying that the distance equals the path
				{
					//route[k++] = path[i];
					markEdge(path[i], path[j]);
					i = j;
					j--;
				}
				else
				{
					j--;
				}
			}
			resettingPens();
		}

		void printShortestDist()
		{
			drawFont = gcnew System::Drawing::Font("Arial", 10);
			drawBrush = gcnew SolidBrush(Color::Red);
			g->DrawString("Shortest Distance:" + distance[destNode].ToString(), drawFont, drawBrush, PointF(700,380));
			resetFont();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Dijkstra()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(1, 1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(873, 400);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 404);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(137, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Enter the number of Nodes:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(166, 427);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"From ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(242, 427);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(20, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"To";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(15, 420);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(59, 20);
			this->textBox1->TabIndex = 4;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(74, 420);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 20);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Go";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Dijkstra::button1_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(166, 404);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(59, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Add Edges";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(195, 422);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(41, 20);
			this->textBox2->TabIndex = 7;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(268, 421);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(42, 20);
			this->textBox3->TabIndex = 8;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(412, 422);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 22);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Add Edge";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Dijkstra::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(647, 407);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(100, 37);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Calculate Shortest Path";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Dijkstra::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(789, 414);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Reset All";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Dijkstra::button4_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(316, 427);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(41, 13);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Weight";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(363, 422);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(43, 20);
			this->textBox4->TabIndex = 13;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(520, 403);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(41, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Source";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(581, 403);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(60, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Destination";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(523, 421);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(38, 20);
			this->textBox5->TabIndex = 16;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(584, 422);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(37, 20);
			this->textBox6->TabIndex = 17;
			// 
			// Dijkstra
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(876, 452);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Dijkstra";
			this->Text = L"Dijkstra";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		//getting number of nodes and drawing them
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		n= Convert::ToInt32(textBox1->Text);
		drawNodes();
		pictureBox1->Refresh();
		clrAdjacency();
	}
			 //getting the edge values and weights and drawing each edge with updating inside the adjacency matrix
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	int a = Convert::ToInt32(textBox2->Text);
	int b = Convert::ToInt32(textBox3->Text);
	int x = Convert::ToInt32(textBox4->Text);
	drawEdge(a, b, x);
	pictureBox1->Refresh();
}

//getting source and destination nodes and finding the shortest path and distance
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	sourceNode = Convert::ToInt32(textBox5->Text);
	destNode = Convert::ToInt32(textBox6->Text);
	calcShortestDist();
	printShortestDist();
	pictureBox1->Refresh();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	array<int, 2>^ adj = gcnew array<int, 2>(10, 10);
	array<int>^ visited = gcnew array<int>(10);
	array<int>^ distance = gcnew array<int>(10);
	array<int>^ path = gcnew array<int>(10);

	int pathIndex = 0;

	infDist();
	clrAdjacency();
	createImage();
}
};
}