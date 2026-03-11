using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public struct ResourceStack
{
    public string type;
    public int amount;
}

[CreateAssetMenu(fileName = "Recipe", menuName = "Scriptable Objects/Resource")]
public class Recipe : ScriptableObject
{
    public List<ResourceStack> inputs; // Max 2 types conseillé
    public ResourceStack output;
    public float processingTime = 2.0f;
}