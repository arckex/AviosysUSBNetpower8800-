using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;

public class USBPower : MonoBehaviour {
    float timer = 0;
    bool on = true;

	// Use this for initialization
	void Start () {
        Init();
        Toggle(on);
        //print("Fan on? " + on);
	}
	
	// Update is called once per frame
	void Update () {
        timer += Time.deltaTime;
        if (timer > 3)
        {
            on = !on;
            Toggle(on);
            timer = 0;
            //print("Fan on? " + on);
        }
	}

    void OnDestroy()
    {
        Toggle(false);
        Close();
    }

    [DllImport("USBPower")]    public static extern void Init();
    [DllImport("USBPower")]    public static extern void Close();
    [DllImport("USBPower")]    public static extern void Toggle(bool fanState);
}
