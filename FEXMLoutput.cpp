#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <iomanip>
#include <sstream>
using namespace std;
void FEXMLoutput(double index_xyz, vector< vector<double> > gcoord, vector< vector<int> > nodes, vector<int> FiberElement,string Filename,int filenumber)
{
	string fname2 = ".vtu";
	string fname;
	for (int i5 = 0; i5 < filenumber; i5++)   //i5总循环数，即生成文件数，需要提前指定
	{
		stringstream i5ss;
		string i5s;
		i5ss << i5;
		i5ss >> i5s;
		fname = Filename + i5s + fname2;  //string Filename = "F:/paraview/m-2Dcdata/FEXML";

		ofstream outFile;
		outFile.open(fname, std::ios::trunc);
		outFile << "<VTKFile type=\"UnstructuredGrid\" version=\"1.0\" byte_order=\"LittleEndian\" header_type=\"UInt64\" compressor=\"vtkZLibDataCompressor\">" << "\n";
		outFile << "  <UnstructuredGrid>" << "\n";
		outFile << "    <Piece NumberOfPoints=\"" << gcoord.size() << "\" NumberOfCells = \"" << FiberElement.size() << "\" > " << "\n";
		outFile << "      <PointData Scalars=\"scalars\">" << "\n";
		outFile << "      </PointData>" << "\n";
		outFile << "      <CellData>" << "\n";
		outFile << "      </CellData>" << "\n";
		outFile << "      <Points>" << "\n";
		outFile << "        <DataArray type=\"Float64\" Name=\"Points\" NumberOfComponents=\"3\" format=\"ascii\" > " << "\n";

		for (int i = 0; i < gcoord.size(); i++)
		{
			outFile << "          " << index_xyz * gcoord[i][0] << " " << index_xyz * gcoord[i][1] << " " << index_xyz * gcoord[i][2] << "\n";
		}

		outFile << "        </DataArray>" << "\n";
		outFile << "      </Points>" << "\n";
		outFile << "      <Cells>" << "\n";

		outFile << "        <DataArray type=\"Int32\" IdType=\"1\" Name=\"connectivity\" format=\"ascii\"> " << "\n";

		for (int i = 0; i < FiberElement.size(); i++)
		{
			outFile << "          " << nodes[FiberElement[i]][0] << " " << nodes[FiberElement[i]][1] << " " << nodes[FiberElement[i]][2] << " " << nodes[FiberElement[i]][3] << "\n";
		}

		outFile << "        </DataArray> " << "\n";
		outFile << "        <DataArray type=\"Int32\" IdType=\"1\" Name=\"offsets\" format=\"ascii\"> " << "\n";
		int orl = FiberElement.size() / 6 + 1;
		int orn = 1;
		for (int i = 0; i < orl; i++)
		{
			outFile << "          ";
			for (int i42 = 0; i42 < 6; i42++)
			{
				outFile << orn * 4 << " ";
				orn++;
				if (orn > FiberElement.size()) break;
			}
			outFile << "\n";
		}
		outFile << "        </DataArray> " << "\n";
		outFile << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << "\n";
		int cell = 10;
		orn = 1;
		for (int i = 0; i < orl; i++)
		{
			outFile << "          ";
			for (int i44 = 0; i44 < 6; i44++)
			{
				outFile << cell << " ";
				orn++;
				if (orn > FiberElement.size())
					break;
			}
			outFile << "\n";
		}
		outFile << "        </DataArray>" << "\n";
		outFile << "      </Cells>" << "\n";
		outFile << "    </Piece>" << "\n";
		outFile << "  </UnstructuredGrid>" << "\n";
		outFile << "</VTKFile>" << "\n";
		outFile.close();
	}
}