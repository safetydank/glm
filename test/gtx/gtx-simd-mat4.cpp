///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2010 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2010-09-16
// Licence : This source is under MIT licence
// File    : test/gtx/simd-mat4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#define GLM_INSTRUCTION_SET GLM_PLATFORM_SSE3 | GLM_PLATFORM_SSE2
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/simd_vec4.hpp>
#include <glm/gtx/simd_mat4.hpp>
#include <glm/gtx/random.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

std::vector<float> test_detA(std::vector<glm::mat4> const & Data)
{
	std::vector<float> Test(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Test.size() - 1; ++i)
		Test[i] = glm::determinant(Data[i]);

	std::clock_t TimeEnd = clock();
	printf("Det A: %d\n", TimeEnd - TimeStart);

	return Test;
}

std::vector<float> test_detB(std::vector<glm::mat4> const & Data)
{
	std::vector<float> Test(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Test.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		Test[i] = glm::simd_vec4(glm::detail::sse_slow_det_ps((__m128 const * const)&m)).x; 
	}

	std::clock_t TimeEnd = clock();
	printf("Det B: %d\n", TimeEnd - TimeStart);

	return Test;
}

std::vector<float> test_detC(std::vector<glm::mat4> const & Data)
{
	std::vector<float> Test(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Test.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		Test[i] = glm::simd_vec4(glm::detail::sse_det_ps((__m128 const * const)&m)).x; 
	}

	std::clock_t TimeEnd = clock();
	printf("Det C: %d\n", TimeEnd - TimeStart);

	return Test;
}

std::vector<float> test_detD(std::vector<glm::mat4> const & Data)
{
	std::vector<float> Test(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Test.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		Test[i] = glm::simd_vec4(glm::detail::sse_detd_ps((__m128 const * const)&m)).x; 
	}

	std::clock_t TimeEnd = clock();
	printf("Det D: %d\n", TimeEnd - TimeStart);

	return Test;
}

void test_invA(std::vector<glm::mat4> const & Data, std::vector<glm::mat4> & Out)
{
	//std::vector<float> Test(Data.size());
	Out.resize(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Out.size() - 1; ++i)
	{
		Out[i] = glm::inverse(Data[i]);
	}

	std::clock_t TimeEnd = clock();
	printf("Inv A: %d\n", TimeEnd - TimeStart);
}

void test_invC(std::vector<glm::mat4> const & Data, std::vector<glm::mat4> & Out)
{
	//std::vector<float> Test(Data.size());
	Out.resize(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Out.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		glm::simd_mat4 o;
		glm::detail::sse_inverse_fast_ps((__m128 const * const)&m, (__m128 *)&o);
		Out[i] = *(glm::mat4*)&o;
	}

	std::clock_t TimeEnd = clock();
	printf("Inv C: %d\n", TimeEnd - TimeStart);
}

void test_invD(std::vector<glm::mat4> const & Data, std::vector<glm::mat4> & Out)
{
	//std::vector<float> Test(Data.size());
	Out.resize(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Out.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		glm::simd_mat4 o;
		glm::detail::sse_inverse_ps((__m128 const * const)&m, (__m128 *)&o);
		Out[i] = *(glm::mat4*)&o;
	}

	std::clock_t TimeEnd = clock();
	printf("Inv D: %d\n", TimeEnd - TimeStart);
}

void test_mulA(std::vector<glm::mat4> const & Data, std::vector<glm::mat4> & Out)
{
	//std::vector<float> Test(Data.size());
	Out.resize(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Out.size() - 1; ++i)
	{
		Out[i] = Data[i] * Data[i];
	}

	std::clock_t TimeEnd = clock();
	printf("Mul A: %d\n", TimeEnd - TimeStart);
}

void test_mulD(std::vector<glm::mat4> const & Data, std::vector<glm::mat4> & Out)
{
	//std::vector<float> Test(Data.size());
	Out.resize(Data.size());

	std::clock_t TimeStart = clock();

	for(std::size_t i = 0; i < Out.size() - 1; ++i)
	{
		_mm_prefetch((char*)&Data[i + 1], _MM_HINT_T0);
		glm::simd_mat4 m(Data[i]);
		glm::detail::sse_mul_ps((__m128 const * const)&m, (__m128 const * const)&m, (__m128*)&Out[i]);
	}

	std::clock_t TimeEnd = clock();
	printf("Mul D: %d\n", TimeEnd - TimeStart);
}

int test_compute_glm()
{
	return 0;
}

int test_compute_gtx()
{
	std::vector<glm::vec4> Output(1000000);

	std::clock_t TimeStart = clock();

	for(std::size_t k = 0; k < Output.size(); ++k)
	{
		float i = float(k) / 1000.f;
		glm::vec3 A = glm::normalize(glm::vec3(i));
		glm::vec3 B = glm::cross(A, glm::vec3(0, 0, 1));
		glm::mat4 C = glm::rotate(glm::mat4(1.0f), i, B);
		glm::mat4 D = glm::scale(C, glm::vec3(0.8f, 1.0f, 1.2f));
		glm::mat4 E = glm::translate(D, glm::vec3(1.4f, 1.2f, 1.1f));
		glm::mat4 F = glm::perspective(i, 1.5f, 0.1f, 1000.f);
		glm::mat4 G = glm::inverse(F * E);
		glm::vec3 H = glm::unProject(glm::vec3(i), G, F, E[3]);
		glm::vec3 I = glm::project(H, G, F, E[3]);
		glm::mat4 J = glm::lookAt(glm::normalize(B), H, I);
		glm::mat4 K = glm::transpose(J);
		glm::quat L = glm::normalize(glm::quat_cast(K));
		glm::vec4 M = L * glm::smoothstep(K[3], J[3], glm::vec4(i));
		glm::mat4 N = glm::mat4(glm::normalize(M), K[3], J[3], glm::vec4(i));
		glm::mat4 O = N * glm::inverse(N);
		glm::vec4 P = O * glm::reflect(N[3], glm::vec4(A, 1.0f));
		glm::vec4 Q = glm::vec4(glm::dot(M, P));
		glm::vec4 R = glm::quat(Q.w, glm::vec3(Q)) * P;
		Output[k] = R;
	}

	std::clock_t TimeEnd = clock();
	printf("test_compute_gtx: %d\n", TimeEnd - TimeStart);

	return Output.size() != 0;
}

int main(int argc, void* argv[])
{
	int Failed = 0;

	std::vector<glm::mat4> Data(1024 * 1024 * 8);
	for(std::size_t i = 0; i < Data.size(); ++i)
		Data[i] = glm::mat4(
			glm::vec4(glm::compRand4(-2.0f, 2.0f)),
			glm::vec4(glm::compRand4(-2.0f, 2.0f)),
			glm::vec4(glm::compRand4(-2.0f, 2.0f)),
			glm::vec4(glm::compRand4(-2.0f, 2.0f)));

	{
		std::vector<glm::mat4> TestInvA;
		test_invA(Data, TestInvA);
	}
	{
		std::vector<glm::mat4> TestInvC;
		test_invC(Data, TestInvC);
	}
	{
		std::vector<glm::mat4> TestInvD;
		test_invD(Data, TestInvD);
	}

	{
		std::vector<glm::mat4> TestA;
		test_mulA(Data, TestA);
	}
	{
		std::vector<glm::mat4> TestD;
		test_mulD(Data, TestD);
	}

	{
		std::vector<float> TestDetA = test_detA(Data);
		std::vector<float> TestDetB = test_detB(Data);
		std::vector<float> TestDetD = test_detD(Data);
		std::vector<float> TestDetC = test_detC(Data);

		for(std::size_t i = 0; i < TestDetA.size(); ++i)
			if(TestDetA[i] != TestDetB[i] && TestDetC[i] != TestDetB[i] && TestDetC[i] != TestDetD[i])
				return 1;
	}

	// shuffle test
	glm::simd_vec4 A(1.0f, 2.0f, 3.0f, 4.0f);
	glm::simd_vec4 B(5.0f, 6.0f, 7.0f, 8.0f);
	__m128 C = _mm_shuffle_ps(A.Data, B.Data, _MM_SHUFFLE(1, 0, 1, 0));

	Failed += test_compute_glm();
	Failed += test_compute_gtx();
	

	system("pause");

	return Failed;
}