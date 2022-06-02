#include "SpaceMenu.h"

#include "IntersectionView.h"
#include "IndexedSortSearchAlgoView.h"
#include "SpaceHashView.h"
#include "CompactSpaceHash3dView.h"
#include "ZOrderSearchView.h"
#include "MarchingCubesView.h"
#include "VolumeView.h"
#include "VolumeConvertView.h"
#include "OctreeView.h"
#include "LinearOctreeView.h"
#include "DynamicOctreeView.h"
#include "SpaceHashView.h"
#include "UniformGrid3dView.h"
#include "MeshToParticleView.h"

#include "SVSphereView.h"
#include "SVBoxView.h"
#include "VoxelSphereView.h"
#include "VoxelizerView.h"
#include "ScanLineVoxelizerView.h"
#include "RayTracerView.h"

#include "CrystalScene/AppBase/MenuItem.h"

using namespace Crystal::Scene;
using namespace Crystal::UI;

SpaceMenu::SpaceMenu(const std::string& name, World* world, Canvas* canvas, ControlPanel* control) :
	IMenu(name, world, canvas)
{
	add(new MenuItem("SpaceHash", [world, canvas, control]() {
		control->setWindow(new SpaceHashView("SpaceHash", world, canvas));
		}));
	add(new MenuItem("CompactSpaceHash", [world, canvas, control]() {
		control->setWindow(new CompactSpaceHash3dView("CompactSpaceHash", world, canvas));
		}));
	add(new MenuItem("IndexedSortSearch", [world, canvas, control]() {
		control->setWindow(new IndexedSortSearchAlgoView("IndexedSort", world, canvas));
		}));
	add(new MenuItem("ZOrderSearch", [world, canvas, control]() {
		control->setWindow(new ZOrderSearchView("ZOrderSearch", world, canvas));
		}));
	add(new MenuItem("Octree", [world, canvas, control]() {
		control->setWindow(new OctreeView("Octree", world, canvas));
		}));
	add(new MenuItem("LinearOctree", [world, canvas, control]() {
		control->setWindow(new LinearOctreeView("LinearOctree", world, canvas));
		}));
	add(new MenuItem("DynamicOctree", [world, canvas, control]() {
		control->setWindow(new DynamicOctreeView("DynamicOctree", world, canvas));
		}));
	add(new MenuItem("Intersection", [world, canvas, control]() {
		control->setWindow(new IntersectionView("Intersection", world, canvas));
		}));
	add(new MenuItem("Volume", [world, canvas, control]() {
		control->setWindow(new VolumeView("Volume", world, canvas));
		}));
	add(new MenuItem("VolumeConvert", [world, canvas, control]() {
		control->setWindow(new VolumeConvertView("VolumeConvert", world, canvas));
		}));
	add(new MenuItem("MarchingCubes", [world, canvas, control]() {
		control->setWindow(new MarchingCubesView("MarchingCubes", world, canvas));
		}));
	add(new MenuItem("UniformGrid", [world, canvas, control]() {
		control->setWindow(new UniformGrid3dView("UniformGrid", world, canvas));
		}));
	add(new MenuItem("MeshToParticle", [world, canvas, control]() {
		control->setWindow(new MeshToParticleView("MeshToParticle", world, canvas));
		}));
	add(new MenuItem("SVSphere", [world, canvas, control]() {
		control->setWindow(new SVSphereView("SVSphere", world, canvas));
		}));
	add(new MenuItem("SVBox", [world, canvas, control]() {
		control->setWindow(new SVBoxView("SVBox", world, canvas));
		}));
	add(new MenuItem("VoxelSphere", [world, canvas, control]() {
		control->setWindow(new VoxelSphereView("VoxelSphere", world, canvas));
		}));
	add(new MenuItem("Voxelizer", [world, canvas, control]() {
		control->setWindow(new VoxelizerView("Voxelizer", world, canvas));
		}));
	add(new MenuItem("ScanLineVoxelizer", [world, canvas, control]() {
		control->setWindow(new ScanLineVoxelizerView("ScanLineVoxelizer", world, canvas));
		}));
	add(new MenuItem("RayTracer", [world, canvas, control]() {
			control->setWindow(new RayTracerView("RayTracer", world, canvas));
		}));
}
