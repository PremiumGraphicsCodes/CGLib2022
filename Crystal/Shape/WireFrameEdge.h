#pragma once

namespace Crystal {
	namespace Shape {

		class WireFrameEdge
		{
		public:
			WireFrameEdge() :
				originId(0),
				destId(0)
			{}

			WireFrameEdge(const int originId, const int destId) :
				originId(originId),
				destId(destId)
			{}

			int originId;
			int destId;
		};

	}
}