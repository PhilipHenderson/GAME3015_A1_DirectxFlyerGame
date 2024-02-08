#include "Aircraft.hpp"
#include "Game.hpp"

Aircraft::Aircraft(Type type, Game* game) : Entity(game)
, mType(type)
{
	switch (type)
	{
	case (Eagle):
		mSprite = "Eagle";
		break;
	case (Raptor):
		mSprite = "Raptor";
		break;
	default:
		mSprite = "Eagle";
		break;
	}
}

void Aircraft::drawCurrent() const
{

	//auto ri = ritems[i];

	//auto vbv = ri->Geo->VertexBufferView();
	//auto ibv = ri->Geo->IndexBufferView();

	//cmdList->IASetVertexBuffers(0, 1, &vbv);
	//cmdList->IASetIndexBuffer(&ibv);
	//cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

	////step18
	//CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
	//tex.Offset(ri->Mat->DiffuseSrvHeapIndex, mCbvSrvDescriptorSize);

	//D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
	//D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;

	////step19
	//cmdList->SetGraphicsRootDescriptorTable(0, tex);
	//cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
	//cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

	//cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);

}
void Aircraft::updateCurrent(const GameTimer& gt) {
	// Check if the aircraft is an enemy
	if (mType == Aircraft::Raptor) {
		// Parameters for circular movement
		static float angle = 0.0f; // Current angle
		float circleRadius = 0.1f; // Radius of the circle
		float speed = -0.1f; // Speed of movement along the circle

		// Calculate the delta angle for this frame
		float deltaAngle = XM_2PI * speed * gt.DeltaTime();

		// Update the current angle
		angle += deltaAngle;

		// Calculate the new position
		float newX = getWorldPosition().x + circleRadius * cosf(angle) / 100.0f;
		float newZ = getWorldPosition().z + circleRadius * sinf(angle) / 100.0f;

		// Set the new position
		setPosition(newX, getWorldPosition().y, newZ);


		setWorldRotation(0, -angle + XM_PIDIV2, 0);
	}

	// Call base class update to handle common update behavior
	Entity::updateCurrent(gt);

	// Any additional player-specific update logic can go here
}



void Aircraft::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->World, XMMatrixScaling(10.0f, 1.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

XMFLOAT3 Aircraft::getForwardVector() const {
	float yaw = mWorldRotation.y;
	return XMFLOAT3(sinf(yaw), 0.0f, cosf(yaw));
}




