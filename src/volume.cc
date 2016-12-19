#include <nan.h>

#ifdef OS_WIN
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#endif

NAN_METHOD(whoAmI) {
  auto message = Nan::New<v8::String>("Volume!").ToLocalChecked();
  info.GetReturnValue().Set(message);
}

NAN_METHOD(getVolume)
{
  float currentVolume = 0;
#if defined(OS_WIN)
  HRESULT hr;

  CoInitialize(NULL);
  IMMDeviceEnumerator *deviceEnumerator = NULL;
  hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
  IMMDevice *defaultDevice = NULL;

  hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
  deviceEnumerator->Release();
  deviceEnumerator = NULL;

  IAudioEndpointVolume *endpointVolume = NULL;
  hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
  defaultDevice->Release();
  defaultDevice = NULL;

  hr = endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
  endpointVolume->Release();
  CoUninitialize();
#elseif
  Nan::Throw
#elif defined(OS_LINUX)
  Nan::ThrowError("Not Implemented");
#elif defined(OS_MAC)
  Nan::ThrowError("Not Implemented");
#endif

  info.GetReturnValue().Set(Nan::New<v8::Number>(currentVolume));
}
