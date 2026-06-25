#pragma once
#include <string>
#include <vulkan/vulkan.h>

class Mesh {
public:
  Mesh(std::string InPath);
  ~Mesh();

  void Draw(VkCommandBuffer InCommand);

private:
  VkDevice Device = VK_NULL_HANDLE;
  VkBuffer VertexBuffer = VK_NULL_HANDLE;
  VkDeviceMemory VertexBufferMemory = VK_NULL_HANDLE;
  VkBuffer IndexBuffer = VK_NULL_HANDLE;
  VkDeviceMemory IndexBufferMemory = VK_NULL_HANDLE;
  uint32_t VertexCount = 0;
  uint32_t IndexCount = 0;
};