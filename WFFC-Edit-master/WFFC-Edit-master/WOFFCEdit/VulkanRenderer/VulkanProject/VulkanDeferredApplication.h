#pragma once
#include "Window.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "Camera.h"
#include "Plane.h"
#include "PlaneMesh.h"
#include "ImportedModel.h"
#include <atltypes.h>


#define TEX_DIMENSIONS 2048;

class VulkanDeferredApplication : public VulkanWindow
{
public:
	VulkanDeferredApplication(Renderer* renderer, int width, int height)
		:VulkanWindow(renderer, width, height)
	{
		InitialiseVulkanApplication();
	}

	VulkanDeferredApplication(Renderer* renderer, int width, int height, HINSTANCE instance, HWND window)
		:VulkanWindow(renderer, width, height, instance, window)
	{
	}

	~VulkanDeferredApplication();

	struct uboVS {
		glm::mat4 projection;
		glm::mat4 view;
	};
	struct vertice {
		VkPipelineVertexInputStateCreateInfo inputState;
		VkVertexInputBindingDescription bindingDescriptions;
		std::array<VkVertexInputAttributeDescription,3> attributeDescriptions;
	};

	struct UboDataDynamic
	{
		glm::mat4 *model = nullptr;
	} uboDataDynamic;

	struct UboTextureDataDynamic
	{
		VkSampler *sampler = nullptr;
	} uboTextureDataDynamic;


	struct {
		VkDescriptorSet cube;
		VkDescriptorSet house;
	}descriptorSets;




	void CreateCamera();
	void InitialiseVulkanApplication();
	void Update(CRect screenRect);
	void DrawFrame() override;
	void _CreateOutlinePipeline();
	void _CreateGraphicsPipeline() override;
	void _CreateShadowPipeline();
	void UpdateUniformBuffer(uint32_t currentImage);
	VkPipelineShaderStageCreateInfo loadShader(std::string fileName, VkShaderStageFlagBits stage);
	void _CreateGeometry();
	void _CreateRenderPass() override;
	void _CreateCommandBuffers() override;
	void _CreateVertexDescriptions();
	void _CreateDescriptorPool() override;
	void _CreateDescriptorSets() override;
	void _CreateDescriptorSetLayout() override;
	void _CreateShaderBuffer(VkDevice device, VkDeviceSize size, VkBuffer* vertexBuffer, VkDeviceMemory* vertexBufferMemory, VkBufferUsageFlagBits bufferStage, void *data);
	void SetUpUniformBuffers();
	void CreateShadowRenderPass();
	void CreateGBuffer();
	void CreateShadowPassCommandBuffers();
	void CreateDeferredCommandBuffers();

	vertice vertices;
	uboVS offScreenUniformVSData;
	uboVS fullScreenUniformVSData;

	ScreenTarget* screenTarget;
	PlaneMesh* planeMesh;
	ImportedModel* houseModel;


	size_t dynamicAlignment;
	size_t dynamicTextureAlignment;

	VkDescriptorSetLayout offScreenDescriptorSetLayout;
	VkDescriptorSetLayout deferredDescriptorSetLayout;

	VkDescriptorSetLayout shadowDescriptorSetLayout;
	VkDescriptorSet shadowDescriptorSet;
	vk::wrappers::ShadowFrameBuffer shadowFrameBuffer;

	VkDescriptorSet descriptorSet;
	VkDescriptorSet descriptorPool;
	
	vk::wrappers::GFrameBuffer deferredOffScreenFrameBuffer;
	VkSampler colorSampler;

	VkSemaphore presentCompleteSemaphore;
	VkSemaphore renderCompleteSemaphore;
	VkSemaphore offScreenSemaphore;
	VkSemaphore shadowSemaphore;

	VkCommandBuffer shadowCmdBuffer;
	VkCommandBuffer offScreenCmdBuffer;

	Camera* camera;

	vk::wrappers::Buffer lightViewMatrixBuffer;

	glm::mat4 testLightViewMatrix;
	vk::wrappers::Buffer dynamicUboBuffer;
	vk::wrappers::Buffer dynamicTextureUboBuffer;

	vk::wrappers::Buffer fullScreenVertexUBOBuffer;
	vk::wrappers::Buffer offScreenVertexUBOBuffer;



};
